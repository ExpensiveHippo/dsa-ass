#include "../include/Init.h"
#include "../include/Models/Administrator.h"
#include "../include/Models/User.h"
#include "../include/DataStructures/HashMap.h"
#include <iostream>
#include <Windows.h>

int main() {
	SetConsoleOutputCP(CP_UTF8); // properly display utf8 characters
	Vector<Movie*> movies = initMovies();
	Vector<Actor*> actors = initActors();

	HashMap<Movie*> hMovies;
	HashMap<Actor*> hActors;
	Administrator admin(hActors, hMovies);

	for (int i = 0; i < movies.length(); i++) {
		Movie* m = movies.get(i);
		hMovies.add(m->getName(), m);
	}

	for (int i = 0; i < actors.length(); i++) {
		Actor* a = actors.get(i);
		hActors.add(a->getName(), a);
	}
  
  Administrator admin;
	User user;

	admin.addActorToMovie("Emma Watson", "Rain Man");
	admin.updateActor("Emma Watson");
	admin.updateMovie("Rain Man");

	admin.addMovie(movies);
	user.displayActorsByAge(actors);
	user.displayRecentMovies(movies);
}
