#include "../../include/Utils/IOUtils.h"
#include "../../include/Utils/StringUtils.h"

#include <stdlib.h>
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

Actor* chooseActor(Vector<Actor*>& actors) {
	if (actors.length() == 0) {
		throw std::invalid_argument("Error choosing actor: Vector is empty");
	}

	if (actors.length() == 1) {
		return actors.get(0);
	}

	int len = actors.length();
	int choice = -1;

	std::cout << "\n[INFO] Duplicates found:\n\n";
	for (int i = 0; i < len; i++) {
		std::cout << "[" << i+1 << "] ";
		actors.get(i)->print();
		std::cout << "\n";
	}

	do {
		std::cout << "\nEnter choice: ";
		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > len) {
			std::cout << "[ERROR] Invalid choice.";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return actors.get(choice - 1);
		}
	} while (true);
}

Movie* chooseMovie(Vector<Movie*>& movies) {
	if (movies.length() == 0) {
		throw std::invalid_argument("Error choosing movie: Vector is empty");
	}

	if (movies.length() == 1) {
		return movies.get(0);
	}

	int len = movies.length();
	int choice = -1;

	std::cout << "[INFO] Duplicates found:" << std::endl;
	for (int i = 0; i < len; i++) {
		std::cout << "[" << i << "] ";
		movies.get(i)->print();
		std::cout << std::endl;
	}

	do {
		std::cout << "\nEnter choice: ";
		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > len) {
			std::cout << "[ERROR] Invalid choice. ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return movies.get(choice - 1);
		}
	} while (true);
}

void clearScreen() {
	system("cls");
}

