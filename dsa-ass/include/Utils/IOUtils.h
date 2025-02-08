/*
* NAME: RYAN HO
* ID: S10261024
* GROUP: glorp
*/

#pragma once

#include <string>
#include "../../include/DataStructures/Vector.h"
#include "../../include/Models/Actor.h"
#include "../../include/Models/Movie.h"


const std::string QUITCOMMAND = ":q";

/*
@brief Get a validated (not empty) string from the user

@param prompt - The prompt to display to the user
@param s - The string to store the validated input
@param abort - Allow user to quit by entering command to quit (default ":q")

@return bool - True if the process was aborted
*/
bool getValidatedString(std::string prompt, std::string& s, bool abort = true);

/*
@brief Get a validated int from the user

@param prompt - The prompt to display to the user
@param i - The int to store the validated input
@param abort - Allow user to quit by entering command to quit (default ":q")

@return bool - True if process was aborted
*/
bool getValidatedUInt(std::string prompt, int& i, bool abort = true);

/*
@brief Get an actor from a list of actors

@param actors - The list of actors to choose from

@return Actor* - The chosen actor
*/
Actor* chooseActor(Vector<Actor*>& actors);

/*
@brief Get a movie from a list of movies

@param movies - The list of movies to choose from

@return Movie* - The chosen movie
*/
Movie* chooseMovie(Vector<Movie*>& movies);

