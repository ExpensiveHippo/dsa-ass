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
	totalRatingCount(0)
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
		throw std::out_of_range("ERROR] Rating should be between 0 - 5 inclusive");
	}

	totalRating += rating;
	totalRatingCount++;
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

void Actor::print() {
	std::cout << "[ACTOR]"
		<< "\nID: " << id
		<< "\nName: " << name
		<< "\nBirth Year: " << birthYear
		<< std::endl;
}
