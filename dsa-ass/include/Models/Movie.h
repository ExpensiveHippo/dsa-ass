#pragma once

#include "../DataStructures/Vector.h"
#include "Actor.h"

#include <string>
#include <cstdint>

class Movie
{
private:
	int id;
	std::string name;
	std::string plot;
	int year;
	Vector<Actor*> actors;

public:
	// default constructor 
	Movie();
	Movie(int id, std::string name, std::string plot, int year);
	void setName(std::string newName);
	std::string getName();
	void setPlot(std::string newPlot);
	std::string getPlot();
	void setYear(int newYear);
	int getYear();
	void addActor(Actor* actor);
	void print();
};

