#include "../../include/Models/Administrator.h"
#include "../../include/Utils/IOUtils.h"
#include "../../include/Utils/StringUtils.h"

#include <iostream>
#include <string.h>
#include <cstdint>
#include <limits>
#include <stdexcept>

Administrator::Administrator(
	HashMap<Vector<Actor*>>& actorNameMap, 
	HashMap<Vector<Movie*>>& movieNameMap, 
	HashMap<Actor*>& actorIdMap, 
	HashMap<Movie*>& movieIdMap
)
	: actorNameMap(actorNameMap), 
	movieNameMap(movieNameMap),
	movieIdMap(movieIdMap),
	actorIdMap(actorIdMap) {}

void Administrator::addActor(int id, std::string name, int birthYear) {

	Actor* a = new Actor(id, name, birthYear);

	if (actorIdMap.hasKey(std::to_string(id))) {
		throw std::runtime_error("[ERROR] There is already an actor with id: " + std::to_string(id));
	}

	actorIdMap.add(std::to_string(id), a);
	
	if (actorNameMap.hasKey(name)) {

		// if key already exists, update vector
		Vector<Actor*>& aVec = actorNameMap.get(name);
		aVec.push(a);
	}
	else {

		// if key doesn't exist, create new vector
		Vector<Actor*> aVec;
		aVec.push(a);
		actorNameMap.add(name, aVec);
	}

	// show success message
	std::cout << "\n[SUCCESS] Actor added successfully!\n\n[ADDED]\n" << std::endl;
	a->print();
}

void Administrator::addActor(Actor* actor) {
	int id = actor->getId();
	std::string name = actor->getName();

	if (actorIdMap.hasKey(std::to_string(id))) {
		throw std::runtime_error("[ERROR] There is already an actor with id: " + std::to_string(id));
	}

	actorIdMap.add(std::to_string(id), actor);
	
	if (actorNameMap.hasKey(name)) {

		// if key already exists, update vector
		Vector<Actor*>& aVec = actorNameMap.get(name);
		aVec.push(actor);
	}
	else {

		// if key doesn't exist, create new vector
		Vector<Actor*> aVec;
		aVec.push(actor);
		actorNameMap.add(name, aVec);
	}
}

void Administrator::addMovie(int id, std::string name, std::string plot, int year) {

	Movie* m = new Movie(id, name, plot, year);

	if (movieIdMap.hasKey(std::to_string(id))) {
		throw std::runtime_error("[ERROR] There is already a movie with id: " + std::to_string(id));
	}
	
	movieIdMap.add(std::to_string(id), m);

	if (movieNameMap.hasKey(name)) {

		// if key already exists, update vector
		Vector<Movie*>& mVec = movieNameMap.get(name);
		mVec.push(m);
	}
	else {

		// if key doesn't exist, create new vector
		Vector<Movie*> mVec;
		mVec.push(m);
		movieNameMap.add(name, mVec);
	}

	// show success message 
	std::cout << "\n[SUCCESS] Movie added successfully!\n\n[ADDED]\n" << std::endl;
	m->print();
}

void Administrator::addMovie(Movie* movie) {
	int id = movie->getId();
	std::string name = movie->getName();

	if (movieIdMap.hasKey(std::to_string(id))) {
		throw std::runtime_error("[ERROR] There is already a movie with id: " + std::to_string(id));
	}

	movieIdMap.add(std::to_string(id), movie);
	
	if (movieNameMap.hasKey(name)) {

		// if key already exists, update vector
		Vector<Movie*>& mVec = movieNameMap.get(name);
		mVec.push(movie);
	}
	else {

		// if key doesn't exist, create new vector
		Vector<Movie*> mVec;
		mVec.push(movie);
		movieNameMap.add(name, mVec);
	}
}

void Administrator::addActorToMovie(std::string actorName, std::string movieName) {
	if (!actorNameMap.hasKey(actorName)) {
		throw std::invalid_argument("[ERROR]: Actor \"" + actorName + "\" not found");
	}

	if (!movieNameMap.hasKey(movieName)) {
		throw std::invalid_argument("[ERROR]: Movie \"" + movieName + "\" not found");
	}

	Vector<Actor*> aVec = actorNameMap.get(actorName);
	Vector<Movie*> mVec = movieNameMap.get(movieName);
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
	if (!actorNameMap.hasKey(actorName)) {
		throw std::invalid_argument("[ERROR]: Actor " + actorName + " not found");
	}

	std::string newName;
	std::string newBirthYear;

	Vector<Actor*> aVec = actorNameMap.get(actorName);
	Actor* a = chooseActor(aVec);

	std::cout << "[UPDATING ACTOR DETAILS]" << std::endl;

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

	// show update changes 
	std::cout << "\n[CHANGES]" << std::endl;
	if (newBirthYear.empty() && newName.empty()) {
		std::cout << "No changes made" << std::endl;
	}
	else {
		if (!newName.empty()) {
			std::cout << "Name: " << a->getName() << " -> " << newName << std::endl;
			a->setName(newName);
		}

		if (!newBirthYear.empty()) {
			std::cout << "Birth Year: " << a->getBirthYear() << " -> " << newBirthYear << std::endl;
			a->setBirthYear(std::stoi(newBirthYear));
		}
	}

	// show result 
	std::cout << "\n[FINAL RESULT]\n";
	a->print();
}

void Administrator::updateMovie(std::string movieName) {
	if (!movieNameMap.hasKey(movieName)) {
		throw std::invalid_argument("[ERROR]: Movie " + movieName + " not found");
	}

	std::string newName;
	std::string newPlot;
	std::string newYear;

	Vector<Movie*> mVec = movieNameMap.get(movieName);
	Movie* m = chooseMovie(mVec);

	std::cout << "\n[UPDATING MOVIE DETAILS]" << std::endl;

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

	// print update changes 
	std::cout << "\n[CHANGES]" << std::endl;
	if (newName.empty()
		&& newPlot.empty()
		&& newYear.empty()) {
		std::cout << "No changes made" << std::endl;
	}
	else {
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

	}

	// show result
	std::cout << "\n[FINAL RESULT]\n";
	m->print();
}
