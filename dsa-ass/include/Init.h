#pragma once

#include "DataStructures/Vector.h"
#include "Models/Movie.h"
#include "Models/Actor.h"

#include <string>

const std::string MOVIES_FILE = "resource/movies.csv";
const std::string ACTORS_FILE = "resource/actors.csv";

/*
@brief Returns a vector that represents the fields in the given string

@param field - A line from a csv file

@returns Vector<std::string> A vector containing each field
*/
Vector<Vector<std::string>> parseCSVFile(std::string field, bool removeHeader = true);


// initialise movies from movies.csv
Vector<Movie*> initMovies();

// initialise actors from actors.csv
Vector<Actor*> initActors();


