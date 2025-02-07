#pragma once

#include "../DataStructures/Vector.h"
#include "Actor.h"

#include <string>
#include <cstdint>
class Actor;
class Movie
{
private:
	int id;
	std::string name;
	std::string plot;
	int year;
	int totalRating;
	int totalRatingCount;
	Vector<Actor*> actors;

public:
	// default constructor 
	Movie();
	Movie(int id, std::string name, std::string plot, int year);
	int getId();
	void setName(std::string newName);
	std::string getName();
	void setPlot(std::string newPlot);
	std::string getPlot();
	void setYear(int newYear);
	int getYear();
	Vector<Actor*> getActors();
	void addActor(Actor* actor);
	void addRating(int rating);
	float getRating();
	int getTotalRatingCount();
	void print();
	bool operator<(const Movie& other) const;
	bool operator>(const Movie& other) const;

};

