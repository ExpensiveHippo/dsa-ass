/*
* NAME: RYAN HO, ASHTON CHONG
* ID: S10261024, S10257765
* GROUP: glorp
*/

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
	int totalRating;
	int totalRatingCount;
	Vector<Movie*> movies; 
public:
	// default constructor
	Actor();

	/*
	@brief Constructor for Actor

	@param id - actor's ID
	@param name - actor's name
	@param birthYear - actor's birth year
	*/
	Actor(int id, std::string name, int birthYear);

	/*
	@brief Retrieve actor's ID 

	@returns int - actor's ID
	*/
	int getId();

	/*
	@brief Update actor's name

	@param name - new name

	@returns void
	*/
	void setName(std::string name);

	/*
	@brief Retrieve actor's name

	@returns std::string - actor's name
	*/
	std::string getName();

	/*
	@brief Retrieve actor's birth year

	@returns int - actor's birth year
	*/
	int getBirthYear();

	/*
	@brief Update actor's birth year

	@param birthYear - new birth year

	@returns void
	*/
	void setBirthYear(int birthYear);

	/*
	@brief Retrieve actor's rating

	@returns float - actor's rating
	*/
	float getRating();

	/*
	@brief Add a rating for the user if rating is between 0 and 5 inclusive. Else, throw an out_of_range exception.

	@param rating - rating 

	@returns void
	*/
	void addRating(int rating);

	/*
	@brief Get the total number of ratings for the actor

	@returns int - total number of ratings
	*/
	int getTotalRatingCount();

	/*
	@brief Retrieve all the movies the actor was part of

	@returns Vector<Movie*> - A vector of pointer to movie objects that the actor was part of
	*/
	Vector<Movie*> getMovies();

	/*
	@brief Add an association to a movie that the actor was a part of

	@param movie - the pointer to the movie
	
	@returns void
	*/
	void addMovie(Movie* movie);

	/* 
	@brief Prints the content of the actor object

	@returns void
	*/
	void print();

	/*
	@brief Compares current actor's age with another actor

	@returns bool - true if this actor's birth year is less than the other, else false
	*/
	bool operator>(const Actor& other) const;	

	/*
	@brief Compares current actor's age with another actor

	@returns bool - true if this actor's birth year is more than the other, else false
	*/
	bool operator<(const Actor& other) const;
};

