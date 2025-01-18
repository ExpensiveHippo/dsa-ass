#include "init.h"

#include <fstream>
#include <iostream>

Vector<std::string> split(std::string& s, std::string delimiter) {
	size_t pos; // track position of string seen
	size_t len = delimiter.length();
	std::string token;
	Vector<std::string> tokens; 
	
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		tokens.push(token);
		s.erase(0, pos + len);
	}
	tokens.push(s);
	
	return tokens;
}

std::string replace(std::string s, std::string oldStr, std::string newStr) {
	size_t pos;
	size_t len = newStr.length() > 0 ? newStr.length() : 1;
	
	while ((pos = s.find(oldStr)) != std::string::npos) {
		s.replace(pos, len, newStr);
	}

	return s;
}

Vector<Movie*> initMovies() {
	std::ifstream file("movies.csv");
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
	std::ifstream file("actors.csv");
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
