#include "../include/Init.h"
#include "../include/Utils/IOUtils.h"
#include "../include/Models/Administrator.h"
#include "../include/DataStructures/HashMap.h"

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
void printUserMenu();
void printAdminMenu();
int getUserOption();
Actor* chooseActor(Vector<Actor*>& actorNameVec);
Movie* chooseMovie(Vector<Movie*>& movieNameVec);
void addActorRating(HashMap<Vector<Actor*>>& hActors);
void addMovieRating(HashMap<Vector<Movie*>>& hMovies);
void displayActorRating(HashMap<Vector<Actor*>>& aVec);
void displayMovieRating(HashMap<Vector<Movie*>>& mVec);
void addActor(Administrator& admin);
void addMovie(Administrator& admin);
void addActorToMovie(Administrator& admin);
void updateActor(Administrator& admin);
void updateMovie(Administrator& admin);

int main() {
	SetConsoleOutputCP(CP_UTF8); // properly display utf8 characters
	std::cout << std::fixed << std::setprecision(1); // 1dp for ratings

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
			option = getUserOption();
			std::cout << "\n";
			switch (option) {
			case 0:
				role = NONE;
				break;
			case 6:
				addActorRating(hActors);
				break;
			case 7:
				addMovieRating(hMovies);
				break;
			case 8:
				displayActorRating(hActors);
				break;
			case 9:
				displayMovieRating(hMovies);
				break;
			default:
				break;
			}
			clearScreen();
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
	std::cout << "[6] Add rating to actor" << std::endl;
	std::cout << "[7] Add rating to movie" << std::endl;
	std::cout << "[8] Display rating of actor" << std::endl;
	std::cout << "[9] Display rating of movie" << std::endl;
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

Actor* chooseActor(Vector<Actor*>& actorNameVec) {
	if (actorNameVec.length() == 0) {
		throw std::invalid_argument("Error choosing actor: Vector is empty");
	}

	if (actorNameVec.length() == 1) {
		return actorNameVec.get(0);
	}

	int len = actorNameVec.length();
	int choice = -1;

	std::cout << "[INFO] Duplicates found:" << std::endl;
	for (int i = 0; i < len; i++) {
		std::cout << "[" << i << "] ";
		actorNameVec.get(i)->print();
	}

	do {
		std::cout << "\nEnter choice: ";
		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > len) {
			std::cout << "Invalid choice. ";
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
		else {
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			return actorNameVec.get(choice - 1);
		}
	} while (true);

}

Movie* chooseMovie(Vector<Movie*>& movieNameVec) {
	if (movieNameVec.length() == 0) {
		throw std::invalid_argument("Error choosing movie: Vector is empty");
	}

	if (movieNameVec.length() == 1) {
		return movieNameVec.get(0);
	}

	int len = movieNameVec.length();
	int choice = -1;

	std::cout << "[INFO] Duplicates found:" << std::endl;
	for (int i = 0; i < len; i++) {
		std::cout << "[" << i << "] ";
		movieNameVec.get(i)->print();
	}

	do {
		std::cout << "\nEnter choice: ";
		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > len) {
			std::cout << "Invalid choice. ";
			std::cin.clear();
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		}
		else {
			std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
			return movieNameVec.get(choice - 1);
		}
	} while (true);


}

void addActorRating(HashMap<Vector<Actor*>>& hActors) {
	bool abort;
	std::string actorName;
	int rating;
	
	std::cout << "-------ADDING ACTOR RATING---------\n";

	do {
		abort = getValidatedString("Enter actor name (or \":q\" to quit): ", actorName);
		if (abort) {
			return;
		}

		if (!hActors.hasKey(actorName)) {
			std::cout << "[ERROR] Actor \"" << actorName << "\" does not exist\n";
			continue;
		}

		Vector<Actor*> aVec = hActors.get(actorName);
		Actor* a = chooseActor(aVec);
		
		std::cout << actorName << "'s current rating: " << a->getRating() << " (" << a->getTotalRatingCount() << ")" << std::endl;

		while (true) {
			abort = getValidatedUInt("Enter rating (0-5 or \":q\" to quit): ", rating);
			if (abort) {
				return;
			}
			try {
				a->addRating(rating);
				break;
			}
			catch (const std::out_of_range& err) {
				std::cout << err.what() << std::endl;
			}
		}

	} while (true);
}

void addMovieRating(HashMap<Vector<Movie*>>& hMovies) {
	bool abort;
	std::string movieName;
	int rating;
	
	std::cout << "-------ADDING MOVIE RATING---------\n";

	do {
		abort = getValidatedString("Enter movie name (or \":q\" to quit): ", movieName);
		if (abort) {
			return;
		}

		if (!hMovies.hasKey(movieName)) {
			std::cout << "[ERROR] Movie\"" << movieName << "\" does not exist\n";
			continue;
		}

		Vector<Movie*> mVec = hMovies.get(movieName);
		Movie* m = chooseMovie(mVec);

		std::cout << movieName << "'s current rating: " << m->getRating() << " (" << m->getTotalRatingCount() << ")" << std::endl;

		while (true) {
			abort = getValidatedUInt("Enter rating (0-5 or \":q\" to quit): ", rating);
			if (abort) {
				return;
			}
			try {
				m->addRating(rating);
				std::cout << "[SUCCESS] Current movie rating is " << m->getRating();
				break;
			}
			catch (const std::out_of_range& err) {
				std::cout << err.what() << std::endl;
			}
		}
	} while (true);

}

void displayActorRating(HashMap<Vector<Actor*>>& hActors) {
	bool abort;
	std::string actorName;
	int rating;

	std::cout << "-------DISPLAYING ACTOR RATING---------\n";

	do {
		abort = getValidatedString("Enter actor name (or \":q\" to quit): ", actorName);
		if (abort) {
			return;
		}

		if (!hActors.hasKey(actorName)) {
			std::cout << "[ERROR] Actor \"" << actorName << "\" does not exist\n";
			continue;
		}

		Vector<Actor*> aVec = hActors.get(actorName);
		Actor* a = chooseActor(aVec);

		std::cout << actorName << "'s rating: " << a->getRating() << " (" << a->getTotalRatingCount() << ")" << std::endl;
	} while (true);
}

void displayMovieRating(HashMap<Vector<Movie*>>& hMovies) {
	bool abort;
	std::string movieName;
	
	std::cout << "-------DISPLAYING MOVIE RATING---------\n";

	do {
		abort = getValidatedString("Enter movie name (or \":q\" to quit): ", movieName);
		if (abort) {
			return;
		}

		if (!hMovies.hasKey(movieName)) {
			std::cout << "[ERROR] Movie\"" << movieName << "\" does not exist\n";
			continue;
		}

		Vector<Movie*> mVec = hMovies.get(movieName);
		Movie* m = chooseMovie(mVec);
		
		std::cout << movieName << "'s rating: " << m->getRating() << " (" << m->getTotalRatingCount() << ")" << std::endl;
	} while (true);

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
