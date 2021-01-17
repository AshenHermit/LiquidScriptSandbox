#pragma once

#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <io.h>

namespace utils {

	namespace fs = std::filesystem;

	static std::string ReadFile(std::string filePath) {
		std::ifstream in(filePath);
		in.seekg(0, std::ios::end);
		size_t len = in.tellg();
		in.seekg(0);
		std::string contents(len + 1, '\0');
		in.read(&contents[0], len);
		return contents;
	}

	typedef std::vector<std::string> DirectoryList;
	static DirectoryList GetDirectories(const std::string& d) {
		DirectoryList v;
		for (auto& p : fs::directory_iterator(d))
		{
			if (p.status().type() == fs::file_type::directory) v.push_back(p.path().string());
		}
		return v;
	};

	static std::vector<std::string> GetFiles(const std::string& d) {
		std::vector<std::string> v;
		for (auto& p : fs::directory_iterator(d))
		{
			if (p.status().type() == fs::file_type::regular) {
				v.push_back(p.path().string());
			}
		}
		return v;
	};

	static std::size_t GetFileCount(const std::string& d) {
		return std::distance(fs::directory_iterator(d), fs::directory_iterator{});
	};

	struct KeyPathStruct {
		std::string key;
		std::string path;
	};

	typedef std::vector<KeyPathStruct> KeyPathList;
	static KeyPathList GetKeysAndPaths(const std::string& directory) {
		KeyPathList paths_keys;

		std::vector<std::string> dirs =
			GetDirectories(directory);

		for (int d = 0; d < dirs.size(); d++)
		{
			std::vector<std::string> files = GetFiles(dirs[d]);

			for (int f = 0; f < files.size(); f++)
			{
				std::string key =
					dirs[d].substr(dirs[d].find_last_of("\\") + 1) + "/" +
					files[f].substr(files[f].find_last_of("\\") + 1,
						files[f].find_last_of(".") - files[f].find_last_of("\\") - 1);

				paths_keys.push_back({ key, files[f] });
			}
		}

		return paths_keys;
	}

}