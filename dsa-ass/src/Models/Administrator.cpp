#include "../../include/Models/Administrator.h"
#include "../../include/Utils/IOUtils.h"

#include <iostream>
#include <string.h>
#include <cstdint>
#include <limits>

Administrator::Administrator() {}

void Administrator::addActor(Vector<Actor*>& v) {
	// Generate id or ask user for id?
	uint16_t birthYear;
	uint32_t id;
	std::string name;
	bool validInput;


	std::cout << "--------ADDING ACTOR---------\n";
	do {
		// get actor id
		validInput = getValidatedUint32("ID (or \":q\" to quit): ", id);
		if (!validInput) {
			return;
		}

		// get actor name
		validInput = getValidatedString("Name (or \":q\" to quit): ", name, true);
		if (!validInput) {
			return;
		}

		// get actor birth year
		validInput = getValidatedUint16("Birth Year (or \":q\" to quit): ", birthYear, true);
		if (!validInput) {
			return;
		}	

		// create actor and add to vector
		Actor* a = new Actor(id, name, birthYear);
		v.push(a);

		// show success message and new actor details
		std::cout << "\nActor added successfully!\n" << std::endl;
		a->print();
		std::cout << "\n\n";
	} while (true);
}

void Administrator::addMovie(Vector<Movie*>& v) {
	uint16_t year;
	uint32_t id;
	std::string name, plot;
	bool validInput;

	std::cout << "--------ADDING MOVIE---------\n";

	do {
		// get movie id
		validInput = getValidatedUint32("ID (or \":q\" to quit): ", id);
		if (!validInput) {
			return;
		}

		// get movie name
		validInput = getValidatedString("Name (or \":q\" to quit): ", name, true);
		if (!validInput) {
			return;
		}

		// get movie plot
		validInput = getValidatedString("Plot (or \":q\" to quit): ", plot, true);
		if (!validInput) {
			return;
		}

		// get movie year
		validInput = getValidatedUint16("Year (or \":q\" to quit): ", year, true);
		if (!validInput) {
			return;
		}

		// create movie and add to vector
		Movie* m = new Movie(id, name, plot, year);
		v.push(m);

		// show success message and new movie details
		std::cout << "\nMovie added successfully!\n" << std::endl;
		m->print();
		std::cout << "\n\n";
	} while (true);
}
