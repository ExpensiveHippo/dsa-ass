/*
* NAME: RYAN HO, ASHTON CHONG
* ID: S10261024, (ADD)
* GROUP: glorp
*/

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

	/*
	@brief Constructor for Movie

	@param id - movie's ID
	@param name - movie's name
	@param plot - movie's plot
	@param year - movie's year
	*/
	Movie(int id, std::string name, std::string plot, int year);

	/*
	@brief Retrieve movie's ID

	@returns int - movie's ID
	*/
	int getId();

	/*
	@brief Update movie's name

	@param newName - new name

	@returns void
	*/
	void setName(std::string newName);

	/*
	@brief Retrieve movie's name

	@returns std::string - movie's name
	*/
	std::string getName();

	/*
	@brief Update movie's plot

	@param newPlot - new plot

	@returns void
	*/
	void setPlot(std::string newPlot);

	/*
	@brief Retrieve movie's plot

	@returns std::string - movie's plot
	*/
	std::string getPlot();

	/*
	@brief Update movie's year

	@param newYear - new year

	@returns void
	*/
	void setYear(int newYear);
	
	/*
	@brief Retrieve movie's year

	@returns int - movie's year
	*/
	int getYear();

	/*
	@brief Retrieve all the actors in the movie

	@returns Vector<Actor*> - all the actors in the movie
	*/
	Vector<Actor*> getActors();
	
	/*
	@brief Add an actor to the movie

	@param actor - the pointer to the actor

	@returns void
	*/
	void addActor(Actor* actor);

	/*
	@brief Retrieve movie's rating

	@returns float - movie's rating
	*/
	float getRating();

	/*
	@brief Add a rating for the user if rating is between 0 and 5 inclusive. Else, throw an out_of_range exception.

	@param rating - rating

	@returns void
	*/
	void addRating(int rating);
	
	/*
	@brief Retrieve the total rating count

	@returns int - total rating count
	*/
	int getTotalRatingCount();

	/*
	@brief Print movie details

	@returns void
	*/
	void print();

	/*
	@brief Compare two movies based on their year

	@param other - the other movie

	@returns bool - true if this movie year is more than the other movie, false otherwise
	*/
	bool operator<(const Movie& other) const;

	/*
	@brief Compare two movies based on their year

	@param other - the other movie

	@returns bool - true if this movie year is less than the other movie, false otherwise
	*/
	bool operator>(const Movie& other) const;
};

