#include "../../include/Utils/IOUtils.h"
#include "../../include/Utils/StringUtils.h"

#include <iostream>

bool getValidatedString(std::string prompt, std::string& s, bool abort) {
	std::string input;

	do {
		std::cout << prompt;
		std::getline(std::cin, input);
		if (abort && input == QUITCOMMAND) {
			return false;
		}
		if (!input.empty()) {
			s = input;
			return true;
		}
		std::cout << "[ERROR] Input cannot be empty" << std::endl;
	} while (true);
}

bool getValidatedUint16(std::string prompt, uint16_t& i, bool abort) {
	std::string input;

	do {
		std::cout << prompt;
		std::getline(std::cin, input);
		if (abort && input == QUITCOMMAND) {
			return false;
		}
		if (isValidUint16(input)) {
			i = std::stoul(input);
			return true;
		} 
		std::cout << "[ERROR] Input must be an integer between 0 and 65,535 (inclusive)" << std::endl;
	} while (true);
}

bool getValidatedUint32(std::string prompt, uint32_t& i, bool abort) {
	std::string input;

	do {
		std::cout << prompt;
		std::getline(std::cin, input);
		if (abort && input == QUITCOMMAND) {
			return false;
		}
		if (isValidUint32(input)) {
			i = std::stoul(input);
			return true;
		}
		std::cout << "[ERROR] Input must be an integer between 0 and 4,294,967,295 (inclusive)" << std::endl;
	} while (true);
}
