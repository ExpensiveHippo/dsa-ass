#pragma once
#include <iostream>
#include <cstdint>
#include <string>

class Actor
{
private:
	int id;
	std::string name;
	int birthYear;
public:
	Actor();
	Actor(int id, std::string name, int birthYear);
	int getId();
	void setName(std::string name);
	std::string getName();
	void setBirthYear(int birthYear);
	int getBirthYear();
	void print();
	uint16_t getBirthYear() const;	//getter for comparing age in User.cpp
	bool operator>(const Actor& other) const;	//for comparing age in AVLTree.cpp
	bool operator<(const Actor& other) const;
};

