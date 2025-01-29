#include "../../include/Models/Movie.h"

#include <iostream>

Movie::Movie() : id(0), name(""), plot(""), year(0) { }

Movie::Movie(int id, std::string name, std::string plot, int year) 
	: id(id), 
	name(name), 
	plot(plot),
	year(year),
	totalRating(0),
	totalRatingCount(0),
	actors(Vector<Actor*>())
{ }

int Movie::getId() {
	return id;
}

void Movie::setName(std::string newName) {
	name = newName;
}

std::string Movie::getName() {
	return name;
}

void Movie::setPlot(std::string newPlot) {
	plot = newPlot;
}

std::string Movie::getPlot() {
	return plot;
}

void Movie::setYear(int newYear) {
	year = newYear;
}

int Movie::getYear() {
	return year;
}

void Movie::addActor(Actor* actor) {
	if (actors.contains(actor)) {
		throw std::invalid_argument("[ERROR] Actor " + actor->getName() + " is already part of Movie " + name);
	}
	actors.push(actor);
}

void Movie::addRating(int rating) {
	if (rating < 0 || rating > 5) {
		throw std::out_of_range("[ERROR] Rating must be between 0 - 5 inclusive.");
	}

	totalRating += rating;
	totalRatingCount++;
}

float Movie::getRating() {
	if (totalRatingCount == 0) {
		return 0;
	}
	return static_cast<float>(totalRating) / totalRatingCount;
}

int Movie::getTotalRatingCount() {
	return totalRatingCount;
}

void Movie::print() {
	std::string strActors = "";
	for (int i = 0; i < actors.length(); i++) {
		strActors.append(actors.get(i)->getName() + ", ");
	}

	// if string is not empty, remove last comma and space
	if (!strActors.empty()) {
		strActors.erase(strActors.end()-2);
	}

	std::cout << "[MOVIE]"
		<< "\nID: " << id
		<< "\nName: " << name
		<< "\nPlot: " << plot
		<< "\nYear: " << year
		<< "\nActors: " << strActors
		<< std::endl;
}
uint16_t Movie::getReleaseYear() {
	return year;
}
bool Movie::operator<(const Movie& other) const {
	return this->year < other.year;
}

bool Movie::operator>(const Movie& other) const {
	return this->year > other.year;
}