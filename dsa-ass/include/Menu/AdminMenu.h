#pragma once

#include "../Models/Administrator.h"

class AdminMenu {
public:
	AdminMenu(Administrator& admin);

	void printAdminMenu();

	void handleAdminChoice(int choice);

	void addActor();

	void addMovie();

	void addActorToMovie();

	void updateActor();

	void updateMovie();

private:
	Administrator& admin;
};

