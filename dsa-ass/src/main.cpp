#include "../include/Init.h"
#include "../include/Utils/IOUtils.h"
#include "../include/Models/Administrator.h"
#include "../include/DataStructures/HashMap.h"

#include <Windows.h>
#include <iostream>
#include <limits>

enum Role {
	NONE,
	USER,
	ADMINISTRATOR,
};

void clearScreen();
void printLogin();
void printUserMenu();
void printAdminMenu();
int getUserOption();
void addActor(Administrator& admin);
void addMovie(Administrator& admin);
void addActorToMovie(Administrator& admin);
void updateActor(Administrator& admin);
void updateMovie(Administrator& admin);

int main() {
	SetConsoleOutputCP(CP_UTF8); // properly display utf8 characters
	Vector<Movie*> movies = initMovies();
	Vector<Actor*> actors = initActors();

	HashMap<Vector<Movie*>> hMovies;
	HashMap<Vector<Actor*>> hActors;
	Administrator admin(hActors, hMovies);

	for (int i = 0; i < movies.length(); i++) {
		Movie* m = movies.get(i);
		admin.addMovie(m);
	}

	for (int i = 0; i < actors.length(); i++) {
		Actor* a = actors.get(i);
		admin.addActor(a);
	}

	bool end = false;
	enum Role role = NONE;

	while (!end) {
		int option;
		switch (role) {
		case USER:
			printUserMenu();
			break;
		case ADMINISTRATOR:
			printAdminMenu();
			option = getUserOption();
			std::cout << "\n";
			switch (option) {
			case 0:
				role = NONE;
				break;
			case 1:
				addActor(admin);
				break;
			case 2:
				addMovie(admin);
				break;
			case 3:
				addActorToMovie(admin);
				break;
			case 4:
				updateActor(admin);
				break;
			case 5:
				updateMovie(admin);
				break;
			default:
				break;
			}
			clearScreen();
			break;
		default:
			printLogin();
			option = getUserOption();
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
			clearScreen();
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

void printUserMenu() {
	std::cout << "--------------USER MENU--------------" << std::endl;
	std::cout << "[0] Sign out" << std::endl;
	std::cout << "[1] Display actors' age (ascending)" << std::endl;
	std::cout << "[2] Display movies from last 3 years (ascending)" << std::endl;
	std::cout << "[3] Display movies an actor starred in (alphabetical)" << std::endl;
	std::cout << "[4] Display actors in that starred in movie (alphabetical)" << std::endl;
	std::cout << "[5] Display a list of actors a particular actor knows" << std::endl;
	std::cout << std::endl;
}

void printAdminMenu() {
	std::cout << "--------------ADMIN MENU--------------" << std::endl;
	std::cout << "[0] Sign out" << std::endl;
	std::cout << "[1] Add new actor" << std::endl;
	std::cout << "[2] Add new movie" << std::endl;
	std::cout << "[3] Add actor to movie" << std::endl;
	std::cout << "[4] Update actor details" << std::endl;
	std::cout << "[5] Update movie details" << std::endl;
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

void addMovie(Administrator& admin) {
	int year;
	int id;
	std::string name, plot;
	bool abort;

	std::cout << "--------ADDING MOVIE---------\n";

	do {
		// get movie id
		abort = getValidatedUInt("ID (or \":q\" to quit): ", id);
		if (abort) {
			return;
		}

		// get movie name
		abort = getValidatedString("Name (or \":q\" to quit): ", name);
		if (abort) {
			return;
		}

		// get movie plot
		abort = getValidatedString("Plot (or \":q\" to quit): ", plot);
		if (abort) {
			return;
		}

		// get movie year
		abort = getValidatedUInt("Year (or \":q\" to quit): ", year, true);
		if (abort) {
			return;
		}

		// create movie and add to vector
		Movie* m = new Movie(id, name, plot, year);

		try {
			admin.addMovie(m);
			// show success message and new movie details
			std::cout << "\n[SUCCESS] Movie added successfully!\n" << std::endl;
			m->print();
			std::cout << "\n\n";
		}
		catch (const std::runtime_error& err) {
			std::cerr << "\n" << err.what();
		}

	} while (true);
}

void addActor(Administrator& admin) {
	// Generate id or ask user for id?
	int birthYear;
	int id;
	std::string name;
	bool abort;


	std::cout << "--------ADDING ACTOR---------\n";
	do {
		// get actor id
		abort = getValidatedUInt("ID (or \":q\" to quit): ", id);
		if (abort) {
			return;
		}

		// get actor name
		abort = getValidatedString("Name (or \":q\" to quit): ", name);
		if (abort) {
			return;
		}

		// get actor birth year
		abort = getValidatedUInt("Birth Year (or \":q\" to quit): ", birthYear);
		if (abort) {
			return;
		}

		// create actor and add to vector
		Actor* a = new Actor(id, name, birthYear);

		try {
			admin.addActor(a);

			// show success message and new actor details
			std::cout << "\n[SUCCESS] Actor added successfully!\n" << std::endl;
			a->print();
			std::cout << "\n\n";
		}
		catch (const std::runtime_error& err) {
			std::cout << "\n" << err.what() << std::endl;
		}
	} while (true);
}

void addActorToMovie(Administrator& admin) {
	std::string actorName;
	std::string movieName;
	bool abort;

	std::cout << "------ADDING ACTOR TO MOVIE---------" << std::endl;

	do {
		abort = getValidatedString("Enter actor name (or \":q\" to quit): ", actorName);
		if (abort) {
			return;
		}

		abort = getValidatedString("Enter movie name (or \":q\" to quit): ", movieName);
		if (abort) {
			return;
		}
		try {
			admin.addActorToMovie(actorName, movieName);
		}
		catch (const std::invalid_argument& err) {
			std::cout << err.what() << std::endl;
		}
	} while (true);
}

void updateActor(Administrator& admin) {
	std::string actorName;
	bool abort;

	do {
		abort = getValidatedString("Enter actor name (or \":q\" to quit): ", actorName);
		if (abort) {
			return;
		}
		
		try {
			admin.updateActor(actorName);
		}
		catch (const std::invalid_argument& err) {
			std::cout << err.what() << std::endl;
		}
	} while (true);
}

void updateMovie(Administrator& admin) {
	std::string movieName;
	bool abort;

	do {
		abort = getValidatedString("Enter movie name (or \":q\" to quit): ", movieName);
		if (abort) {
			return;
		}

		try {
			admin.updateMovie(movieName);
		}
		catch (const std::invalid_argument& err) {
			std::cout << err.what() << std::endl;
		}
	} while (true);
}
