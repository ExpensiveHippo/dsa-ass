#include "../../include/Models/Actor.h"

#include <iostream>

Actor::Actor() 
	: id(0), 
	name(""), 
	birthYear(0),
	totalRating(0),
	totalRatingCount(0)
{}

Actor::Actor(int id, std::string name, int birthYear) 
	: id(id), 
	name(name), 
	birthYear(birthYear),
	totalRating(0),
	totalRatingCount(0),
	movies(Vector<Movie*>())
{}

int Actor::getId() {
	return id;
}

void Actor::setName(std::string newName) {
	name = newName;
}

std::string Actor::getName() {
	return name;
}

void Actor::setBirthYear(int newBirthYear) {
	birthYear = newBirthYear;
}

int Actor::getBirthYear() {
	return birthYear;
}

void Actor::addRating(int rating) {
	if (rating < 0 || rating > 5) {
		throw std::out_of_range("[ERROR] Rating should be between 0 - 5 inclusive");
	}

	totalRating += rating;
	totalRatingCount++;
	std::cout << "\n[RESULT]\n";
	print();
	std::cout << "\n\n";
}

float Actor::getRating() {
	if (totalRatingCount == 0) {
		return 0;
	}
	return static_cast<float>(totalRating) / totalRatingCount;
}

int Actor::getTotalRatingCount() {
	return totalRatingCount;
}

Vector<Movie*> Actor::getMovies() {
	return movies;
}
void Actor::addMovie(Movie* movie) {
	if (movies.contains(movie)) {
		throw std::invalid_argument("Movie " + movie->getName() + " already consists of Actor " + name);
	}
	movies.push(movie);
}
void Actor::print() {
	std::cout << "[ACTOR]"
		<< "\nID: " << id
		<< "\nName: " << name
		<< "\nBirth Year: " << birthYear
		<< "\nRating: " << getRating() << " (" << totalRatingCount << ")"
		<< std::endl;
}

bool Actor::operator>(const Actor& other) const {
	return this->birthYear <= other.birthYear;	//reversed such that actors displayed in ascending order
}

bool Actor::operator<(const Actor& other) const {
	return this->birthYear >= other.birthYear;
}
