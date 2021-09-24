#include "utils.hpp"


namespace txo {

	bool starts_with(const std::string &string, const char c) {
		return string.size() > 0 && string[0] == c;
	}

	bool starts_with(const std::string &string, const char *expr) {
		return string.find(expr) != std::string::npos
			&& string.find(expr) == 0;
	}

	std::string read_file(std::string filePath) {
		std::fstream file(filePath, std::ios::in);
		std::string content;
		std::string line;

		if (file.is_open()) {
			for (std::string line; std::getline(file, line); ) {
				content += line + "\n";
			}
			file.close();
		} else {
			ERR("Failed to open '" << filePath << "'");
		}

		return content;
	}

} // namespace txo
