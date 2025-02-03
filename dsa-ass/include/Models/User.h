#pragma once

#include "Actor.h"
#include "Movie.h"
#include "../DataStructures/Vector.h"
#include <string>
using namespace std;
class User {
public:
	User();

	void displayActorsByAge(Vector<Actor*>& actors);

	void displayRecentMovies(Vector<Movie*>& movies);

	void displayMoviesByActor(string actorName);

	void displayActorsByMovie(string movieName);

	void displayActorsKnown(string actorName);
};