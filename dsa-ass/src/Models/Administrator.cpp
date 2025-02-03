#include "../../include/Models/Administrator.h"
#include "../../include/Utils/IOUtils.h"
#include "../../include/Utils/StringUtils.h"

#include <iostream>
#include <string.h>
#include <cstdint>
#include <limits>

Administrator::Administrator(HashMap<Actor*>& actors, HashMap<Movie*>& movies) 
	: actors(actors), 
	movies(movies) {}

void Administrator::addActor() {
	// Generate id or ask user for id?
	int birthYear;
	int id;
	std::string name;
	bool validInput;


	std::cout << "--------ADDING ACTOR---------\n";
	do {
		// get actor id
		validInput = getValidatedUInt("ID (or \":q\" to quit): ", id);
		if (!validInput) {
			return;
		}

		// get actor name
		validInput = getValidatedString("Name (or \":q\" to quit): ", name, true);
		if (!validInput) {
			return;
		}

		// get actor birth year
		validInput = getValidatedUInt("Birth Year (or \":q\" to quit): ", birthYear, true);
		if (!validInput) {
			return;
		}	

		// create actor and add to vector
		Actor* a = new Actor(id, name, birthYear);
		actors.add(a->getName(), a);

		// show success message and new actor details
		std::cout << "\nActor added successfully!\n" << std::endl;
		a->print();
		std::cout << "\n\n";
	} while (true);
}

void Administrator::addMovie() {
	int year;
	int id;
	std::string name, plot;
	bool validInput;

	std::cout << "--------ADDING MOVIE---------\n";

	do {
		// get movie id
		validInput = getValidatedUInt("ID (or \":q\" to quit): ", id);
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
		validInput = getValidatedUInt("Year (or \":q\" to quit): ", year, true);
		if (!validInput) {
			return;
		}

		// create movie and add to vector
		Movie* m = new Movie(id, name, plot, year);
		movies.add(m->getName(), m);

		// show success message and new movie details
		std::cout << "\nMovie added successfully!\n" << std::endl;
		m->print();
		std::cout << "\n\n";
	} while (true);
}

void Administrator::addActorToMovie(std::string actorName, std::string movieName) {
	if (!actors.hasKey(actorName)) {
		std::cout << "[ERROR]: Actor \"" << actorName << "\" not found";
	}

	if (!movies.hasKey(movieName)) {
		std::cout << "[ERROR]: Movie \"" << movieName << "\" not found";
	}

	Actor* a = actors.get(actorName);
	Movie* m = movies.get(movieName);
	m->addActor(a);
}

void Administrator::updateActor(std::string actorName) {
	if (!actors.hasKey(actorName)) {
		throw std::invalid_argument("[ERROR]: Actor " + actorName + " not found");
	}

	std::string newName;
	std::string newBirthYear;
	Actor* a = actors.get(actorName);
	
	std::cout << "[UPDATING ACTOR DETAILS]" << std::endl;

	// doesn't make sense to change id

	// name
	std::cout << "[NAME]\nCurrent: " << a->getName() << std::endl;
	std::cout << "New (empty if no changes): ";
	std::getline(std::cin, newName);

	// birth year
	std::cout << "[BIRTH YEAR]\nCurrent: " << std::endl;
	while (true) {
		std::cout << "New (empty if no changes): ";
		std::getline(std::cin, newBirthYear);
		if (newBirthYear.empty() || isValidUInt(newBirthYear)) {
			break;
		} 
	}

	std::cout << "[RESULT]" << std::endl;
	if (newBirthYear.empty() && newName.empty()) {
		std::cout << "No changes made" << std::endl;
		return;
	}

	if (!newName.empty()) {
		std::cout << "Name: " << a->getName() << " -> " << newName << std::endl;
		a->setName(newName);
	}

	if (!newBirthYear.empty()) {
		std::cout << "Birth Year: " << a->getBirthYear() << " -> " << newBirthYear << std::endl;
		a->setBirthYear(std::stoi(newBirthYear));
	}

	a->print();
}

void Administrator::updateMovie(std::string movieName) {
	if (!movies.hasKey(movieName)) {
		throw std::invalid_argument("[ERROR]: Movie " + movieName + " not found");
	}

	std::string newName;
	std::string newPlot;
	std::string newYear;
	Movie* m = movies.get(movieName);
	
	std::cout << "[UPDATING MOVIE DETAILS]" << std::endl;

	// doesn't make sense to change id

	// name
	std::cout << "[NAME]\nCurrent: " << m->getName() << std::endl;
	std::cout << "New Name(empty if no changes): ";
	std::getline(std::cin, newName);

	// plot
	std::cout << "[PLOT]\nCurrent: " << m->getPlot() << std::endl;
	std::cout << "New Plot (empty if no changes): ";
	std::getline(std::cin, newPlot);

	// year
	std::cout << "[YEAR]\nCurrent: " << std::endl;
	while (true) {
		std::cout << "New Year (empty if no changes): ";
		std::getline(std::cin, newYear);
		if (newYear.empty() || isValidUInt(newYear)) {
			break;
		} 
	}

	std::cout << "[RESULT]" << std::endl;
	if (newName.empty() 
		&& newPlot.empty()
		&& newYear.empty()) {
		std::cout << "No changes made" << std::endl;
		return;
	}

	if (!newName.empty()) {
		std::cout << "Name: " << m->getName() << " -> " << newName << std::endl;
		m->setName(newName);
	}

	if (!newPlot.empty()) {
		std::cout << "Plot: " << m->getPlot() << " -> " << newPlot << std::endl;
		m->setPlot(newPlot);
	}

	if (!newYear.empty()) {
		std::cout << "Year: " << m->getYear() << " -> " << newYear << std::endl;
		m->setYear(std::stoi(newYear));
	}

	m->print();
}
