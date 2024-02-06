#pragma once
#include <iostream>
#include <vector>
#include <string>

namespace FileIO {
	std::string InnerPath(std::string path);
	std::vector<std::string> GetFileNames(std::string title);
	std::string GetSaveFolderPath(std::string title);
	std::string ReadFileData(std::string file_path);
	int SaveFileData(std::string file_path, std::string data);
	std::vector<std::string> ReadFileLines(std::string file_path);
	int SaveFileLines(std::string file_path, std::vector<std::string> lines);
};