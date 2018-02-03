#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Config
{
private:
	std::string configFile_;
	std::string workPath_;
	bool read();
	bool create();
public:
	Config();
	bool setup();
};