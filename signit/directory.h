#pragma once

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
public:
	Directory(Config *config);
	bool load();
};