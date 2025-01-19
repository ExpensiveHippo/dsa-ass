#pragma once

#include "DataStructures/Vector.h"
#include "Models/Movie.h"
#include "Models/Actor.h"

#include <string>

const std::string MOVIES_FILE = "resource/movies.csv";
const std::string ACTORS_FILE = "resource/actors.csv";

// initialise movies from movies.csv
Vector<Movie*> initMovies();

// initialise actors from actors.csv
Vector<Actor*> initActors();


