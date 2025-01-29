#pragma once
#include <iostream>
#include <cstdint>
#include <string>

class Actor
{
private:
	uint32_t id;
	std::string name;
	uint16_t birthYear;
public:
	Actor();
	Actor(uint32_t id, std::string name, uint16_t birthYear);
	void print();
	uint16_t getBirthYear() const;	//getter for comparing age in User.cpp
	bool operator>(const Actor& other) const;	//for comparing age in AVLTree.cpp
	bool operator<(const Actor& other) const;
};

