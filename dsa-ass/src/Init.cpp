#include "../include/Init.h"
#include "../include/Utils/StringUtils.h"

#include <fstream>
#include <iostream>

Vector<Movie*> initMovies() {
	std::ifstream file(MOVIES_FILE);
	std::string line;
	Vector<Movie*> movies;

	std::getline(file, line); // get rid of headers

	while (std::getline(file, line)) {
		Vector<std::string> data = split(line, ",");
		Movie* m = new Movie(
			std::stoul(data.get(0)),
			replace(data.get(1), ";", ","),
			replace(data.get(2), ";", ","),
			std::stoul(data.get(3))
		);
		movies.push(m);
	}
	file.close();

	return movies;
};

Vector<Actor*> initActors() {
	std::ifstream file(ACTORS_FILE);
	std::string line;
	Vector<Actor*> actors;

	std::getline(file, line); // get rid of headers

	while (std::getline(file, line)) {
		Vector<std::string> data = split(line, ",");
		Actor* a = new Actor(
			std::stoul(data.get(0)),
			replace(data.get(1), "\"", ""),
			std::stoul(data.get(2))
		);
		actors.push(a);
	}
	file.close();

	return actors;
};
