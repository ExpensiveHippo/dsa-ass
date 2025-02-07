#include "../../include/Models/Administrator.h"
#include "../../include/Utils/IOUtils.h"
#include "../../include/Utils/StringUtils.h"

#include <iostream>
#include <string.h>
#include <cstdint>
#include <limits>
#include <stdexcept>

Administrator::Administrator(HashMap<Vector<Actor*>>& actors, HashMap<Vector<Movie*>>& movies) 
	: actors(actors), 
	movies(movies) {}

Actor* Administrator::chooseActor(Vector<Actor*>& aVec) {
	if (aVec.length() == 0) {
		throw std::invalid_argument("Error choosing actor: Vector is empty");
	}

	if (aVec.length() == 1) {
		return aVec.get(0);
	}

	int len = aVec.length();
	int choice = -1;

	std::cout << "[INFO] Duplicates found:" << std::endl;
	for (int i = 0; i < len; i++) {
		std::cout << "[" << i << "] ";
		aVec.get(i)->print();
	}

	do {
		std::cout << "\nEnter choice: ";
		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > len) {
			std::cout << "Invalid choice. ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return aVec.get(choice - 1);
		}
	} while (true);
}

Movie* Administrator::chooseMovie(Vector<Movie*>& mVec) {
	if (mVec.length() == 0) {
		throw std::invalid_argument("Error choosing movie: Vector is empty");
	}

	if (mVec.length() == 1) {
		return mVec.get(0);
	}

	int len = mVec.length();
	int choice = -1;

	std::cout << "[INFO] Duplicates found:" << std::endl;
	for (int i = 0; i < len; i++) {
		std::cout << "[" << i << "] ";
		mVec.get(i)->print();
	}

	do {
		std::cout << "\nEnter choice: ";
		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > len) {
			std::cout << "Invalid choice. ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return mVec.get(choice - 1);
		}
	} while (true);

}

void Administrator::addActor(Actor* a) {
	if (actors.hasKey(a->getName())) {
		Vector<Actor*>& aVec = actors.get(a->getName());
		for (int i = 0; i < aVec.length(); i++) {
			if (aVec.get(i)->getId() == a->getId()) {
				throw std::runtime_error("[ERROR] There is already an actor with id: " + std::to_string(a->getId()));
				return;
			}
		}
		aVec.push(a);
	}
	else {
		Vector<Actor*> aVec;
		aVec.push(a);
		actors.add(a->getName(), aVec);
	}
}

void Administrator::addMovie(Movie* m) {
	if (movies.hasKey(m->getName())) {
		Vector<Movie*>& mVec = movies.get(m->getName());
		for (int i = 0; i < mVec.length(); i++) {
			if (mVec.get(i)->getId() == m->getId()) {
				throw std::runtime_error("[ERROR] There is already a movie with id: " + std::to_string(m->getId()));
			}
		}
		mVec.push(m);
	}
	else {
		Vector<Movie*> mVec;
		mVec.push(m);
		movies.add(m->getName(), mVec);
	}
}

void Administrator::addActorToMovie(std::string actorName, std::string movieName) {
	if (!actors.hasKey(actorName)) {
		throw std::invalid_argument("[ERROR]: Actor \"" + actorName + "\" not found");
	}

	if (!movies.hasKey(movieName)) {
		throw std::invalid_argument("[ERROR]: Movie \"" + movieName + "\" not found");
	}

	Vector<Actor*> aVec = actors.get(actorName);
	Vector<Movie*> mVec = movies.get(movieName);
	Actor* a = chooseActor(aVec);
	Movie* m = chooseMovie(mVec);
	
	try {
		m->addActor(a);
		std::cout << "[RESULT]" << std::endl;
		m->print();
	}
	catch (const std::invalid_argument& err) {
		std::cout << "\n" << err.what() << std::endl;
	}
}

void Administrator::updateActor(std::string actorName) {
	if (!actors.hasKey(actorName)) {
		throw std::invalid_argument("[ERROR]: Actor " + actorName + " not found");
	}

	std::string newName;
	std::string newBirthYear;
	Vector<Actor*> aVec = actors.get(actorName);
	Actor* a = chooseActor(aVec);
	std::cout << "[UPDATING ACTOR DETAILS]" << std::endl;

	// doesn't make sense to change id

	// name
	std::cout << "\n[NAME]\nCurrent: " << a->getName() << std::endl;
	std::cout << "New (empty if no changes): ";
	std::getline(std::cin, newName);

	// birth year
	std::cout << "\n[BIRTH YEAR]\nCurrent: " << std::endl;
	while (true) {
		std::cout << "New (empty if no changes): ";
		std::getline(std::cin, newBirthYear);
		if (newBirthYear.empty() || isValidUInt(newBirthYear)) {
			break;
		}
	}

	std::cout << "\n[RESULT]" << std::endl;
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
	Vector<Movie*> mVec = movies.get(movieName);
	Movie* m = chooseMovie(mVec);
	std::cout << "\n[UPDATING MOVIE DETAILS]" << std::endl;

	// doesn't make sense to change id

	// name
	std::cout << "\n[NAME]\nCurrent: " << m->getName() << std::endl;
	std::cout << "New Name (empty if no changes): ";
	std::getline(std::cin, newName);

	// plot
	std::cout << "\n[PLOT]\nCurrent: " << m->getPlot() << std::endl;
	std::cout << "New Plot (empty if no changes): ";
	std::getline(std::cin, newPlot);

	// year
	std::cout << "\n[YEAR]\nCurrent: " << std::endl;
	while (true) {
		std::cout << "New Year (empty if no changes): ";
		std::getline(std::cin, newYear);
		if (newYear.empty() || isValidUInt(newYear)) {
			break;
		}
	}


	// print updated results
	std::cout << "\n[RESULT]" << std::endl;
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
