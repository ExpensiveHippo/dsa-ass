#pragma once

#include "../../include/Models/Actor.h"
#include "../../include/Models/Movie.h"
#include "../../include/Models/User.h"


class UserMenu {
public:
	UserMenu(
		User& user,
		Vector<Actor*>& actorVector,
		Vector<Movie*>& movieVector,
		HashMap<Vector<Actor*>>& actorNameMap,
		HashMap<Vector<Movie*>>& movieNameMap,
		HashMap<Actor*>& actorIdMap,
		HashMap<Movie*>& movieIdMap
	);

	void printUserMenu();

	void handleUserChoice(int choice);

	void displayActorsByAge();

	void displayRecentMovies();

	void displayMoviesByActor();

	void displayActorsByMovie();

	void displayActorsKnown();

	void addActorRating();

	void addMovieRating();

	void displayActorRating();

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

