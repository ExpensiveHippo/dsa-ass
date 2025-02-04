#pragma once

#include "Actor.h" 
#include "Movie.h"
#include "../DataStructures/HashMap.h"

class Administrator
{
private:
	HashMap<Vector<Actor*>>& actors;
	HashMap<Vector<Movie*>>& movies;

	Actor* chooseActor(Vector<Actor*>& actorName);
	Movie* chooseMovie(Vector<Movie*>& movieName);
public: 
	// default constructor
	Administrator(HashMap<Vector<Actor*>>& actors, HashMap<Vector<Movie*>>& movies);

	// add new actor
	void addActor(Actor* a);

	// add new movie
	void addMovie(Movie* m);

	// add an actor to a movie
	void addActorToMovie(std::string actorName, std::string movieName);

	// update actor details
	void updateActor(std::string actorName);

	// update movie details
	void updateMovie(std::string movieName);
};

