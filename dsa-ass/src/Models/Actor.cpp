#include "../../include/Models/Actor.h"

#include <iostream>

Actor::Actor() : id(0), name(""), birthYear(0) {}

Actor::Actor(int id, std::string name, int birthYear) 
	: id(id)
	, name(name)
	, birthYear(birthYear) {}

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

void Actor::print() {
	std::cout << "[ACTOR]"
		<< "\nID: " << id
		<< "\nName: " << name
		<< "\nBirth Year: " << birthYear
		<< std::endl;
}
