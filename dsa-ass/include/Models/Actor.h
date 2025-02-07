#pragma once
#include "../DataStructures/Vector.h"
#include "Movie.h"
#include <iostream>
#include <cstdint>
#include <string>
class Movie;
class Actor
{
private:
	int id;
	std::string name;
	int birthYear;
	Vector<Movie*> movies;
public:
	Actor();
	Actor(int id, std::string name, int birthYear);
	int getId();
	void setName(std::string name);
	std::string getName();
	void setBirthYear(int birthYear);
	int getBirthYear();
	Vector<Movie*> getMovies();
	void addMovie(Movie* movie);
	void print();
	bool operator>(const Actor& other) const;	//for comparing age in AVLTree.cpp
	bool operator<(const Actor& other) const;
};

