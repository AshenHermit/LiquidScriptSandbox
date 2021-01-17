#pragma once
#include <stdio.h>
#include <windows.h>
#include <eh.h>
#include <exception>

class SE_Exception : public std::exception
{
private:
    const unsigned int nSE;
public:
    SE_Exception() noexcept : SE_Exception{ 0 } {}
    SE_Exception(unsigned int n) noexcept : nSE{ n } {}
    unsigned int getSeNumber() const noexcept { return nSE; }
};

#pragma unmanaged
static void se_trans_func(unsigned int u, EXCEPTION_POINTERS*)
{
    throw SE_Exception(u);
}

class Scoped_SE_Translator
{
private:
    const _se_translator_function old_SE_translator;
public:
    Scoped_SE_Translator(_se_translator_function new_SE_translator) noexcept
        : old_SE_translator{ _set_se_translator(new_SE_translator) } {}
    ~Scoped_SE_Translator() noexcept { _set_se_translator(old_SE_translator); }
};


namespace utils {
    static void SetSETranslator() {
        // Be sure to enable "Yes with SEH Exceptions (/EHa)" in C++ / Code Generation;
        _set_se_translator([](unsigned int u, struct _EXCEPTION_POINTERS* pExp) {
            std::string error = "SE Exception: ";
            switch (u) {
            case 0xC0000005:
                error += "Access Violation";
                break;
            default:
                char result[11];
                sprintf_s(result, 11, "0x%08X", u);
                error += result;
            };
            throw std::exception(error.c_str());
        });
    }
}