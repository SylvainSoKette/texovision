#pragma once

#include <fstream>
#include <iostream>
#include <string>


#define LOG(x) std::cout << "[LOG]: " << x << "\n"
#define WARN(x) std::cout << "[WARNING]: " << x << "\n"
#define ERR(x) std::cerr << "[ERROR]: " << x << std::endl;

namespace txo {

	bool starts_with(const std::string &string, const char c);
	bool starts_with(const std::string &string, const char *expr);
	std::string read_file(std::string);

}