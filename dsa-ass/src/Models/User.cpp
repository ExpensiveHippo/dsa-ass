#pragma once
#include <iostream>
#include <time.h>
#include "../../include/Utils/IOUtils.h"
#include "../../include/Models/User.h"
#include "../../include/DataStructures/AVLTree.h"


User::User() {}

int getCurrentYear() {
	//time initialization
	time_t rawTime = time(nullptr);
	struct tm now;
	localtime_s(&now, &rawTime);
	return now.tm_year + 1900; //tm_year starts from 1900
}
void User::displayActorsByAge(Vector<Actor*>& actors) {
	//initialization
	uint16_t min, max;
	AVLTree<Actor> filteredActors;
	int currentYear = getCurrentYear();
	bool isValid;
	while (true) {
		isValid = getValidatedUint16("Enter minimum age (\":q\" to quit): ", min);
		if (!isValid) {
			return;
		}
		isValid = getValidatedUint16("Enter maximum age {\":q\" to quit): ", max);
		if (!isValid) {
			return;
		}

		break;
	}
	for (int i = 0; i < actors.length(); i++) {
		int age = currentYear - actors.get(i)->getBirthYear();	
		if (age >= min && age <= max) {
			filteredActors.push(actors.get(i));
		}
	}
	cout << "[AVL3]Actors between age " << min << " and " << max << ": " << endl;
	filteredActors.displayInOrder();
}
void User::displayRecentMovies(Vector<Movie*>& movies) {
	AVLTree<Movie> recentMovies;
	for (int i = 0; i < movies.length(); i++) {
		int currentYear = getCurrentYear();
		int releaseYear = movies.get(i)->getReleaseYear();
		if (releaseYear <= currentYear && releaseYear >= currentYear - 3) {
			recentMovies.push(movies.get(i));
		}
	}
	cout << "[AVL3]Movies in the past 3 years" << endl;
	recentMovies.displayInOrder();
}



