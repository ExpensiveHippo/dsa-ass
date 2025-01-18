#pragma once

#include "Vector.h"
#include "Movie.h"
#include "Actor.h"

// helper functions for parsing file
Vector<std::string> split(std::string& s, std::string& delimiter);
std::string replace(std::string s, std::string oldStr, std::string newStr);

// initialise movies from movies.csv
Vector<Movie*> initMovies();

// initialise actors from actors.csv
Vector<Actor*> initActors();


