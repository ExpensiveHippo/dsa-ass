#pragma once

#include "Actor.h" 
#include "Movie.h"
#include "../DataStructures/HashMap.h"

class Administrator
{
private:
	HashMap<Actor*>& actors;
	HashMap<Movie*>& movies;
public: 
	// default constructor
	Administrator(HashMap<Actor*>& actors, HashMap<Movie*>& movies);

	// add new actor
	void addActor();

	// add new movie
	void addMovie();

	// add an actor to a movie
	void addActorToMovie(std::string actorName, std::string movieName);

	// update actor details
	void updateActor(std::string actorName);

	// update movie details
	void updateMovie(std::string movieName);
};

