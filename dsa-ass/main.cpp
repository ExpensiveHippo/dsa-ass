#include "init.h"

#include <iostream>
#include <Windows.h>

int main() {
	SetConsoleOutputCP(CP_UTF8); // properly display utf8 characters
	Vector<Movie*> movies = initMovies();
	Vector<Actor*> actors = initActors();

	for (int i = 0; i < movies.length(); i++) {
		movies.get(i)->print();
		std::cout << std::endl;
	}

	for (int i = 0; i < actors.length(); i++) {
		actors.get(i)->print();
		std::cout << std::endl;
	}
}
