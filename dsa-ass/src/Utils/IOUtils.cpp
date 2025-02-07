#include "../../include/Utils/IOUtils.h"
#include "../../include/Utils/StringUtils.h"

#include <iostream>
#include <limits>

bool getValidatedString(std::string prompt, std::string& s, bool abort) {
	std::string input;

	do {
		std::cout << prompt;
		std::getline(std::cin, input);
		if (abort && input == QUITCOMMAND) {
			return true;
		}
		if (!input.empty()) {
			s = input;
			return false;
		}
		std::cout << "[ERROR] Input cannot be empty" << std::endl;
	} while (true);
}

bool getValidatedUInt(std::string prompt, int& i, bool abort) {
	std::string input;

	do {
		std::cout << prompt;
		std::getline(std::cin, input);
		if (abort && input == QUITCOMMAND) {
			return true;
		}
		if (isValidUInt(input)) {
			i = std::stoul(input);
			return false;
		} 
		std::cout << "[ERROR] Input must be an integer between 0 and " << std::numeric_limits<int>::max() << " (inclusive)" << std::endl;
	} while (true);
}

