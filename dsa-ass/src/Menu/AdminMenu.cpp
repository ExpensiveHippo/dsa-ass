#include "../../include/Menu/AdminMenu.h"
#include "../../include/Utils/IOUtils.h"

AdminMenu::AdminMenu(Administrator& admin) : admin(admin) {}

void AdminMenu::printAdminMenu() {
	std::cout << "--------------ADMIN MENU--------------" << std::endl;
	std::cout << "[0] Sign out" << std::endl;
	std::cout << "[1] Add new actor" << std::endl;
	std::cout << "[2] Add new movie" << std::endl;
	std::cout << "[3] Add actor to movie" << std::endl;
	std::cout << "[4] Update actor details" << std::endl;
	std::cout << "[5] Update movie details" << std::endl;
	std::cout << std::endl;
}

void AdminMenu::handleAdminChoice(int choice) {
	switch (choice) {
	case 1:
		addActor();
		break;
	case 2:
		addMovie();
		break;
	case 3:
		addActorToMovie();
		break;
	case 4:
		updateActor();
		break;
	case 5:
		updateMovie();
		break;
	default:
		break;
	}
}

void AdminMenu::addMovie() {
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

		try {
			admin.addMovie(id, name, plot, year);
		}
		catch (const std::runtime_error& err) {
			std::cerr << "\n" << err.what();
		}

	} while (true);
}

void AdminMenu::addActor() {
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

void AdminMenu::addActorToMovie() {
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

void AdminMenu::updateActor() {
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

void AdminMenu::updateMovie() {
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

