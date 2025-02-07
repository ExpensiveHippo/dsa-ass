#include "../include/Init.h"
#include "../include/Utils/IOUtils.h"
#include "../include/Models/Administrator.h"
#include "../include/Models/User.h"
#include "../include/DataStructures/HashMap.h"
#include <iostream>
#include <Windows.h>

int main() {
	SetConsoleOutputCP(CP_UTF8); // properly display utf8 characters
	HashMap<Actor*> actorMap;	// map of actors <id, Actor*>
	HashMap<Movie*> movieMap;	// map of movies <id, Movie*>
	Vector<Movie*> movies = initMovies(movieMap);
	Vector<Actor*> actors = initActors(actorMap);
	initCast(actorMap, movieMap);	// add actors to movies

	HashMap<Vector<Movie*>> hMovies;
	HashMap<Vector<Actor*>> hActors;
	Administrator admin(hActors, hMovies);
	User user;
	for (int i = 0; i < movies.length(); i++) {
		Movie* m = movies.get(i);
		admin.addMovie(m);
	}

	for (int i = 0; i < actors.length(); i++) {
		Actor* a = actors.get(i);
		admin.addActor(a);
	}
	/*user.displayActorsByAge(actors);
	user.displayRecentMovies(movies);
	user.displayActorsByMovie(hMovies);
	user.displayMoviesByActor(hActors);*/
	user.displayActorsKnown(hActors);
	//admin.addActorToMovie("Tom Jansen", "My Grandfather and the Man in the Moon");
	
}

void addMovie(Administrator& admin) {
	int year;
	int id;
	std::string name, plot;
	bool validInput;

	std::cout << "--------ADDING MOVIE---------\n";

	do {
		// get movie id
		validInput = getValidatedUInt("ID (or \":q\" to quit): ", id);
		if (!validInput) {
			return;
		}

		// get movie name
		validInput = getValidatedString("Name (or \":q\" to quit): ", name, true);
		if (!validInput) {
			return;
		}

		// get movie plot
		validInput = getValidatedString("Plot (or \":q\" to quit): ", plot, true);
		if (!validInput) {
			return;
		}

		// get movie year
		validInput = getValidatedUInt("Year (or \":q\" to quit): ", year, true);
		if (!validInput) {
			return;
		}

		// create movie and add to vector
		Movie* m = new Movie(id, name, plot, year);

		admin.addMovie(m);

		// show success message and new movie details
		std::cout << "\n[SUCCESS] Movie added successfully!\n" << std::endl;
		m->print();
		std::cout << "\n\n";
	} while (true);
}

void addActor(Administrator& admin) {
	// Generate id or ask user for id?
	int birthYear;
	int id;
	std::string name;
	bool validInput;


	std::cout << "--------ADDING ACTOR---------\n";
	do {
		// get actor id
		validInput = getValidatedUInt("ID (or \":q\" to quit): ", id);
		if (!validInput) {
			return;
		}

		// get actor name
		validInput = getValidatedString("Name (or \":q\" to quit): ", name, true);
		if (!validInput) {
			return;
		}

		// get actor birth year
		validInput = getValidatedUInt("Birth Year (or \":q\" to quit): ", birthYear, true);
		if (!validInput) {
			return;
		}

		// create actor and add to vector
		Actor* a = new Actor(id, name, birthYear);
		admin.addActor(a);

		// show success message and new actor details
		std::cout << "\n[SUCCESS] Actor added successfully!\n" << std::endl;
		a->print();
		std::cout << "\n\n";
	} while (true);
}
