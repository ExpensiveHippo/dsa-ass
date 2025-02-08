#pragma once

#include "Actor.h" 
#include "Movie.h"
#include "../DataStructures/HashMap.h"

class Administrator
{
private:
	HashMap<Vector<Actor*>>& actorNameMap;
	HashMap<Vector<Movie*>>& movieNameMap;
	HashMap<Actor*>& actorIdMap;
	HashMap<Movie*>& movieIdMap;

public: 
	// default constructor
	Administrator(
		HashMap<Vector<Actor*>>& actorNameMap,
		HashMap<Vector<Movie*>>& movieNameMap,
		HashMap<Actor*>& actorIdMap,
		HashMap<Movie*>& movieIdMap);

	// add new actor
	void addActor(int id, std::string name, int birthYear);
	void addActor(Actor* actor);

	// add new movie
	void addMovie(int id, std::string name, std::string plot, int year);
	void addMovie(Movie* movie);

	// add an actor to a movie
	void addActorToMovie(std::string actorName, std::string movieName);

	// update actor details
	void updateActor(std::string actorName);

	// update movie details
	void updateMovie(std::string movieName);
};

