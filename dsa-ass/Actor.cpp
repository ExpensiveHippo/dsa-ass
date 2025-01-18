#include "Actor.h"

#include <iostream>

Actor::Actor() : id(0), name(""), birthYear(0) {}

Actor::Actor(uint32_t id, std::string name, uint16_t birthYear) 
	: id(id)
	, name(name)
	, birthYear(birthYear) {}

void Actor::print() {
	std::cout << "[ACTOR]"
		<< "\nID: " << id
		<< "\nName: " << name
		<< "\nBirth Year: " << birthYear
		<< std::endl;
}
