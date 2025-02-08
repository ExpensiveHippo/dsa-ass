/*
* NAME: RYAN HO
* ID: S10261024
* GROUP: glorp
*/
#pragma once

#include "../../include/Models/Actor.h"
#include "../../include/Models/Movie.h"
#include "../../include/Models/User.h"


class UserMenu {
public:

	/*
	@brief Constructor for UserMenu

	@param user - the user object
	@param actorVector - the vector of actor objects
	@param movieVector - the vector of movie objects
	@param actorNameMap - the hashmap of actor names
	@param movieNameMap - the hashmap of movie names
	@param actorIdMap - the hashmap of actor ids
	@param movieIdMap - the hashmap of movie ids
	*/
	UserMenu(
		User& user,
		Vector<Actor*>& actorVector,
		Vector<Movie*>& movieVector,
		HashMap<Vector<Actor*>>& actorNameMap,
		HashMap<Vector<Movie*>>& movieNameMap,
		HashMap<Actor*>& actorIdMap,
		HashMap<Movie*>& movieIdMap
	);

	/*
	@brief Print the functions that the user can access

	@returns void
	*/
	void printUserMenu();

	/*
	@brief Call the function that the user wants to access

	@param choice - the number associated with the function

	@returns void
	*/
	void handleUserChoice(int choice);

	/*
	@brief Calls the corresponding user function

	@returns void
	*/
	void displayActorsByAge();

	/*
	@brief Call the corresponding user function

	@returns void
	*/
	void displayRecentMovies();

	/*
	@brief Call the corresponding user function

	@returns void
	*/
	void displayMoviesByActor();

	/*
	@brief Call the corresponding user function

	@returns void
	*/
	void displayActorsByMovie();

	/*
	@brief Call the corresponding user function

	@returns void
	*/
	void displayActorsKnown();

	/*
	@brief Prompts for an actor and the rating to give

	@returns void
	*/
	void addActorRating();

	/*
	@brief Prompts for a movie and the rating to give

	@returns void
	*/
	void addMovieRating();

	/*
	@brief Prompts for an actor and display the rating

	@returns void
	*/
	void displayActorRating();

	/*
	@brief Prompts for a movie and display the rating

	@returns void
	*/
	void displayMovieRating();

private:
	User& user;
	Vector<Actor*>& actorVector;
	Vector<Movie*>& movieVector;
	HashMap<Vector<Actor*>>& actorNameMap;
	HashMap<Vector<Movie*>>& movieNameMap;
	HashMap<Actor*>& actorIdMap;
	HashMap<Movie*>& movieIdMap;
};

