/*
* NAME: RYAN HO
* ID: S10261024
* GROUP: glorp
*/
#pragma once

#include "../Models/Administrator.h"

class AdminMenu {
public:
	// constructor
	AdminMenu(Administrator& admin);

	/*
	@brief Print the functions an admin can access

	@returns void
	*/
	void printAdminMenu();

	/*
	@brief Call the function that the admin wants to access

	@param choice - the number associated with the function

	@returns void
	*/
	void handleAdminChoice(int choice);
	
	/*
	@brief Prompt for information of the new actor to add, which is then passed to admin

	@returns void
	*/
	void addActor();

	/*
	@brief Prompt for information of the new movie to add, which is then passed to admin

	@returns void
	*/
	void addMovie();

	/*
	@brief Prompt for the name of the actor and movie, which is then passed to admin

	@returns void
	*/
	void addActorToMovie();

	/*
	@brief Prompt for the name of the actor, which is then passed to admin

	@returns void
	*/
	void updateActor();

	/*
	@brief Prompt for the name of the movie, which is then passed to admin

	@returns void
	*/
	void updateMovie();

private:
	Administrator& admin;
};

