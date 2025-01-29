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
	int totalRating;
	int totalRatingCount;
public:
	Actor();
	Actor(int id, std::string name, int birthYear);
	int getId();
	void setName(std::string name);
	std::string getName();
	void setBirthYear(int birthYear);
	int getBirthYear();
	void addRating(int rating);
	float getRating();
	int getTotalRatingCount();
	void print();
	uint16_t getBirthYear() const;	//getter for comparing age in User.cpp
	bool operator>(const Actor& other) const;	//for comparing age in AVLTree.cpp
	bool operator<(const Actor& other) const;
};

