#pragma once
#include <string>

#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")

#define CURL_STATICLIB 
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <curl/curl.h>

#include "Graphics/Graphics.h"

class RequestManager
{

public:
	CURL* ch;
	CURLcode rv;

	std::string response_body;

	RequestManager();
	~RequestManager();
	std::string Get(std::string url);

	static CURLcode sslctx_function(CURL* curl, void* sslctx, void* parm);
	static size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data);
};

