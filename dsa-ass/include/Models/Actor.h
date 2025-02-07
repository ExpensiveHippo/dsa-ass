#pragma once

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
};

