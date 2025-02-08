/*
* NAME: ASHTON CHONG
* ID: S10257765
* GROUP: glorp
*/

#pragma once

#include "Actor.h"
#include "Movie.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/AVLTree.h"
#include "../DataStructures/HashMap.h"
#include <string>
using namespace std;

class User {
public:
	/*
	@brief Constructor for User
	*/
	User();

	/*
	@brief Display actors by age
	@param actors - vector of actor objects
	@returns void
	*/
	void displayActorsByAge(Vector<Actor*>& actors);

	/*
	@brief Display recent movies (3 years)
	@param movies - vector of movie objects
	@returns void
	*/
	void displayRecentMovies(Vector<Movie*>& movies);

	/*
	@brief Display movies an actor has casted for
	@param actors - hashmap of actor objects
	@returns void
	*/
	void displayMoviesByActor(HashMap<Vector<Actor*>>& actors);

	/*
	@brief Display actors starred in a movie
	@param movies - hashmap of movie objects
	@returns void
	*/
	void displayActorsByMovie(HashMap<Vector<Movie*>>& movies);
	
	/*
	@brief Display actors known by an actor, extending by one separation
	@param actors - hashmap of actor objects
	@returns void
	*/
	void displayActorsKnown(HashMap<Vector<Actor*>>& actors);
	/*
	@brief Display actors sorted by rating, user inputs a rating and the function displays actors with the same or higher rating
	@param actors - vector of actor objects
	@returns void
	*/
	void displayActorsByRating(Vector<Actor*>& actors);

	/*
	@brief Display movies sorted by rating, user inputs a rating and the function displays movies with the same or higher rating
	@param movies - vector of movie objects
	@returns void
	*/
	void displayMoviesByRating(Vector<Movie*>& movies);
};