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
	User();

	void displayActorsByAge(Vector<Actor*>& actors);

	void displayRecentMovies(Vector<Movie*>& movies);

	void displayMoviesByActor(HashMap<Vector<Actor*>>& actors);

	void displayActorsByMovie(HashMap<Vector<Movie*>>& movies);

	void displayActorsKnown(HashMap<Vector<Actor*>>& actors);
};