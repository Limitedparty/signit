#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class Config
{
private:
	std::string configFile_;
	std::string workPath_;
	std::string regexSearch_;
	bool read();
	bool create();
	bool keyset(std::string key, std::string value);
public:
	Config();
	bool setup();

	std::string getWorkPath() { return workPath_; };
	std::string getRegexSearch() { return regexSearch_; };
};