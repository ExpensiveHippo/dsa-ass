/*
* NAME: RYAN HO
* ID: S10261024
* GROUP: glorp
*/

#pragma once

#include "Actor.h" 
#include "Movie.h"
#include "../DataStructures/HashMap.h"

class Administrator
{
private:
	Vector<Actor*> actorVector;
	Vector<Movie*> movieVector;
	HashMap<Vector<Actor*>>& actorNameMap;
	HashMap<Vector<Movie*>>& movieNameMap;
	HashMap<Actor*>& actorIdMap;
	HashMap<Movie*>& movieIdMap;

public: 
	/*
	@brief Constructor for Administrator

	@param actorVector - vector of actor objects
	@param movieVector - vector of movie objects
	@param actorNameMap - hashmap of actor names
	@param movieNameMap - hashmap of movie names
	@param actorIdMap - hashmap of actor ids
	@param movieIdMap - hashmap of movie ids
	*/
	Administrator(
		Vector<Actor*>& actorVector,
		Vector<Movie*>& movieVector,
		HashMap<Vector<Actor*>>& actorNameMap,
		HashMap<Vector<Movie*>>& movieNameMap,
		HashMap<Actor*>& actorIdMap,
		HashMap<Movie*>& movieIdMap);

	/*
	@brief Add an actor to the hashmaps if they do not exist, as well as to the vector

	@param id - id of the actor
	@param name - name of the actor
	@param birthYear - birth year of the actor

	@returns void
	*/
	void addActor(int id, std::string name, int birthYear);

	/*
	@brief Add an actor to the hashmaps if they do not exist

	@param actor - pointer to the actor object

	@returns void
	*/
	void addActor(Actor* actor);

	/*
	@brief Add a movie to the hashmaps if it does not exist, as well as to the vector

	@param id - id of the movie
	@param name - name of the movie
	@param plot - plot of the movie
	@param year - year of the movie

	@returns void
	*/
	void addMovie(int id, std::string name, std::string plot, int year);

	/*
	@brief Add a movie to the hashmaps if it does not exist

	@param movie - pointer to the movie object

	@returns void
	*/
	void addMovie(Movie* movie);

	/*
	@brief Add a actor to a movie, and the movie to the actor, if both exists. Else, throw invalid_argument exception

	@param actorName - name of the actor
	@param movieName - name of the movie

	@returns void
	*/
	void addActorToMovie(std::string actorName, std::string movieName);
	
	/*
	@brief Prompt for updated actor details if the actor exists. Else, throw invalid_argument exception

	@param actorName - name of the actor

	@returns void
	*/
	void updateActor(std::string actorName);

	/*
	@brief Prompt for updated movie details if the movie exists. Else, throw invalid_argument exception

	@param movieName - name of the movie

	@returns void
	*/
	void updateMovie(std::string movieName);
};

