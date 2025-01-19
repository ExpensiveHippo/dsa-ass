#pragma once

#include "Actor.h" 
#include "Movie.h"
#include "../DataStructures/Vector.h"

class Administrator
{
public: 
	// default constructor
	Administrator();

	// add new actor
	void addActor(Vector<Actor*>& v);

	// add new movie
	void addMovie(Vector<Movie*>& m);

	// add an actor to a movie
	void addActorToMovie();

	// update actor details
	void updateActor();

	// update movie details
	void updateMovie();
};

