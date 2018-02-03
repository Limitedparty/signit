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
	bool read();
	bool create();
	bool keyset(std::string key, std::string value);
public:
	Config();
	bool setup();

	std::string getWorkPath() { return workPath_; };
};