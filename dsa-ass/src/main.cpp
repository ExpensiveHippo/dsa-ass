#include "../include/Init.h"
#include "../include/Utils/IOUtils.h"
#include "../include/Models/Administrator.h"
#include "../include/Models/User.h"
#include "../include/DataStructures/HashMap.h"
#include "../include/Menu/UserMenu.h"
#include "../include/Menu/AdminMenu.h"

#include <Windows.h>
#include <iostream>
#include <limits>
#include <iomanip>

enum Role {
	NONE,
	USER,
	ADMINISTRATOR,
};

void clearScreen();
void printLogin();
int getUserOption();

int main() {
	SetConsoleOutputCP(CP_UTF8); // properly display utf8 characters
	std::cout << std::fixed << std::setprecision(1); // 1dp for ratings

	Vector<Movie*> movies = initMovies();
	Vector<Actor*> actors = initActors();
	HashMap<Actor*> actorIdMap;
	HashMap<Movie*> movieIdMap;
	HashMap<Vector<Actor*>> actorNameMap;
	HashMap<Vector<Movie*>> movieNameMap;
	User user;
	Administrator admin(actorNameMap, movieNameMap, actorIdMap, movieIdMap);
	UserMenu userMenu(user, actors, movies, actorNameMap, movieNameMap, actorIdMap, movieIdMap);
	AdminMenu adminMenu(admin);

	for (int i = 0; i < movies.length(); i++) {
		Movie* m = movies.get(i);
		admin.addMovie(m);
	}

	for (int i = 0; i < actors.length(); i++) {
		Actor* a = actors.get(i);
		admin.addActor(a);
	}

	initCast(actorIdMap, movieIdMap);

	bool end = false;
	enum Role role = NONE;

	while (!end) {
		int option;
		switch (role) {
		case USER:
			userMenu.printUserMenu();
			option = getUserOption();
			clearScreen();
			if (option == 0) {
				role = NONE;
			}
			else {
				userMenu.handleUserChoice(option);
			}
			break;
		case ADMINISTRATOR:
			adminMenu.printAdminMenu();
			option = getUserOption();
			clearScreen();
			if (option == 0) {
				role = NONE;
			}
			else {
				adminMenu.handleAdminChoice(option);
			}
			break;
		default:
			printLogin();
			option = getUserOption();
			clearScreen();
			switch (option) {
			case 0:
				end = true;
				break;
			case 1:
				role = USER;
				break;
			case 2:
				role = ADMINISTRATOR;
				break;
			default:
				break;
			}
			break;
		}
	}
}

void clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

void printLogin() {
	std::cout << "--------------LOGIN--------------" << std::endl;
	std::cout << "[0] Quit program" << std::endl;
	std::cout << "[1] Login as User" << std::endl;
	std::cout << "[2] Login as Administrator" << std::endl;
	std::cout << std::endl;
}

int getUserOption() {
	int option; 

	std::cout << "Enter choice: ";
	while (!(std::cin >> option)) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		std::cout << "[ERROR] Invalid input. Please enter a number: ";
	}
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	return option;
}
