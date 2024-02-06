#include "FileIO.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <atlstr.h>
#include <shlobj_core.h>
#include <filesystem>
#include "ProtableFileDialogs.h" //For Open Files with Multiplatforms

using namespace FileIO;
using namespace std;

std::string FileIO::InnerPath(std::string path) {
	return path;
}

vector<string> FileIO::GetFileNames(string title) {
	auto selection = pfd::open_file(title, "", { 
		"Plain Sequence Format (*.txt, *.dna, *.seq, *.plasmid)", "*.txt *.dna *.seq *.plasmid",
		"All Files (*.)", "*" 
	}, pfd::opt::force_path | pfd::opt::multiselect).result();
	return selection;
}

string FileIO::GetSaveFolderPath(string title) {
	auto selection = pfd::select_folder(title).result();
	return selection;
}

std::string FileIO::ReadFileData(std::string file_path) {
	FILE* f;
	string data;
	fopen_s(&f, file_path.c_str(), "rb");
	while (feof(f) == 0) {
		data.push_back(fgetc(f));
	}
	fclose(f);
	data.pop_back();
	return data;
}

int FileIO::SaveFileData(std::string file_path, std::string data) {
	FILE* f;
	fopen_s(&f, file_path.c_str(), "wb");
	for (int i = 0; i < data.size(); i++) {
		fputc(data[i], f);
	}
	fclose(f);
    return 0;
}

std::vector<std::string> FileIO::ReadFileLines(std::string file_path) {
	string data = ReadFileData(file_path);
	vector<string> lines;
	string line;
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == '\n') {
			lines.push_back(line);
			line.clear();
		}
		else {
			line.push_back(data[i]);
		}
	}
	return lines;
}

int FileIO::SaveFileLines(std::string file_path, std::vector<std::string> lines) {
	string line = "";
	for (int i = 0; i < lines.size(); i++) {
		line += lines[i] + "\n";
	}
	SaveFileData(file_path, line);
	return 0;
}
