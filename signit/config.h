#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

struct Sign {
	std::string start; 
	std::string text;
	std::string end;
	int spaces;
};

class Config
{
private:
	std::string configFile_;
	std::string workPath_;
	std::string regexSearch_;
	Sign sign_;
	bool read();
	bool create();
	bool keyset(std::string key, std::string value);
public:
	Config();
	bool setup();

	std::string getWorkPath() { return workPath_; };
	std::string getRegexSearch() { return regexSearch_; };
	Sign getSign() { return sign_; };
};