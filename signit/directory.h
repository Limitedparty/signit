#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>
#include <regex>
#include "config.h"

namespace fs = std::experimental::filesystem;

class Directory
{
private:
	Config *config_;
	std::vector<std::string> filesPaths;
	void addSign(std::string &filetext);
public:
	Directory(Config *config);
	void load();
	void operation();
};