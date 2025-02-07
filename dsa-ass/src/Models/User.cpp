#pragma once
#include <iostream>
#include <time.h>
#include "../../include/Utils/IOUtils.h"
#include "../../include/Models/User.h"


User::User() {}
template <typename T>
using CompareFunction = bool(*)(const T*, const T*);	//function pointer to compare two different pointer objects (actors,movies)
/*INITIALIZATION of necessary functions*/
int getCurrentYear() {
	//time initialization
	time_t rawTime = time(nullptr);
	struct tm now;
	localtime_s(&now, &rawTime);
	return now.tm_year + 1900; //tm_year starts from 1900
}
//functions for CompareFunction<T>
bool compareActorsByName(Actor* a1, Actor* a2) {
	return a1->getName() < a2->getName();  
}
bool compareMoviesByName(Movie* m1, Movie* m2) {
	return m1->getName() < m2->getName();
}


//MERGE SORT ALGORITHM
template<typename T>
void merge(Vector<T*>& items, int left, int mid, int right, CompareFunction<T> compare){
	int	n1 = mid - left + 1; //first half of 'items'
	int n2 = right - mid; //second half of 'items'
	Vector<T*> leftItems;
	Vector<T*> rightItems;
	//copy data to temp vectors leftItems and rightItems
	for (int i = 0; i < n1; i++) {
		leftItems.push(items.get(left + i));
	}
	for (int i = 0; i < n2; i++) {
		rightItems.push(items.get(mid + 1 + i));	
	}
	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		//returns true if leftItems[i] name is less than rightItems[j] name
		if (compare(leftItems.get(i), rightItems.get(j))) {
			items.get(k) = leftItems.get(i);
			i++;
		}
		else {
			items.get(k) = rightItems.get(j);
			j++;
		}
		k++;
	}
	//copy remaining elements of leftItems
	while (i < n1) {
		items.get(k) = leftItems.get(i);
		i++;
		k++;
	}
	//copy remaining elements of rightItems
	while (j < n2) {
		items.get(k) = rightItems.get(j);
		j++;
		k++;
	}
}

template<typename T>
void mergeSort(Vector<T*>& items, int left, int right, CompareFunction<T> compare) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(items, left, mid, compare);
		mergeSort(items, mid + 1, right, compare);
		merge(items, left, mid, right, compare);
	}
}



void User::displayActorsByAge(Vector<Actor*>& actors) {
	//initialization
	int min, max;
	AVLTree<Actor> filteredActors;
	int currentYear = getCurrentYear();
	bool isValid;
	while (true) {
		isValid = getValidatedUInt("Enter minimum age (\":q\" to quit): ", min);
		if (isValid) {
			return;
		}
		isValid = getValidatedUInt("Enter maximum age {\":q\" to quit): ", max);
		if (isValid) {
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
	filteredActors.displayInOrder();
}
void User::displayRecentMovies(Vector<Movie*>& movies) {
	AVLTree<Movie> recentMovies;
	for (int i = 0; i < movies.length(); i++) {
		int currentYear = getCurrentYear();
		int releaseYear = movies.get(i)->getYear();
		if (releaseYear <= currentYear && releaseYear >= currentYear - 3) {
			recentMovies.push(movies.get(i));
		}
	}
	recentMovies.displayInOrder();
}
void User::displayActorsByMovie(HashMap<Vector<Movie*>>& movies) {

	//initialization
	string movieName;
	bool isValid;
	while (true) {
		isValid = getValidatedString("Enter movie name (\":q\" to quit): ", movieName);
		if (isValid) {
			return;
		}
		break;
	}
	if (!movies.hasKey(movieName)) {
		cout << "Movie name: \"" << movieName << "\" not found" << endl;
		return;
	}
	Vector<Actor*> actors = movies.get(movieName).get(0)->getActors();
	if (actors.length() > 1) {
		int actorLength = static_cast<int>(actors.length());
		mergeSort<Actor>(actors, 0, actorLength - 1, (CompareFunction<Actor>)compareActorsByName);
	}
	cout << "Actors in the movie name: \"" << movieName << "\"" << endl;
	for (int i = 0; i < actors.length(); i++) {
		cout << i + 1 << ". " << actors.get(i)->getName() << endl;
	}
}
void User::displayMoviesByActor(HashMap<Vector<Actor*>>& actors) {
	//initialization
	string actorName;
	bool isValid;
	while (true) {
		isValid = getValidatedString("Enter actor name (\":q\" to quit): ", actorName);
		if (isValid) {
			return;
		}
		break;
	}
	Vector<Movie*> movies = actors.get(actorName).get(0)->getMovies();
	if (movies.length() > 1) {
		int movieLength = static_cast<int>(movies.length());
		mergeSort<Movie>(movies, 0, movieLength - 1, (CompareFunction<Movie>)compareMoviesByName);
	}
	cout << "Movies by actor name: \"" << actorName << "\"" << endl;
	for (int i = 0; i < movies.length(); i++) {
		cout << i + 1 << ". " << movies.get(i)->getName() << endl;
	}
}
void User::displayActorsKnown(HashMap<Vector<Actor*>>& actors) {
	//Onboarding process (getName of actor user inputs)
	string actorName;
	bool isValid;
	while (true) {
		isValid = getValidatedString("Enter actor name (\":q\" to quit): ", actorName);
		if (isValid) {
			return;
		}
		break;
	}
	if (!actors.hasKey(actorName)) {
		cout << "Actor name: \"" << actorName << "\" not found" << endl;
		return;
	}
	Actor* actor = actors.get(actorName).get(0);
	//initialization for BFS
	Vector<Actor*> knownActors;
	HashMap<bool> visited; 
	Vector<Actor*> toVisit; 

	toVisit.push(actor);	//starts with the actor chosen by user
	visited.add(actor->getName(), true);	//mark chosen actor as visited

	size_t level = 0;
	//A two-level BFS
	while (toVisit.length() > 0 && level < 2) { 
		Vector<Actor*> nextLevelActors; // to store the next level of actors

		for (size_t i = 0; i < toVisit.length(); i++) {
			// Get co-actors (direct connections)
			Actor* currentActor = toVisit.get(i);	
			for (size_t j = 0; j < currentActor->getMovies().length(); j++) {  // 
				Movie* movie = currentActor->getMovies().get(j);
				for (size_t k = 0; k < movie->getActors().length(); k++) {  // Assuming Movie has an actors vector
					Actor* coActor = movie->getActors().get(k);
					if (coActor != actor && !visited.hasKey(coActor->getName())) {
						knownActors.push(coActor);	//a standalone vector for displaying purposes.
						nextLevelActors.push(coActor);	//stores immediate actors to visit other known actors in the next level
						visited.add(coActor->getName(), true);
					}
				}
			}
		}

		
		toVisit = nextLevelActors;
		level++;
	}

	// Display results
	if (knownActors.length() <= 0) {
		cout << actorName << " does not have any known actors." << endl;
	}
	else {
		cout << "Actors known by " << actorName << ":\n";
		for (size_t i = 0; i < knownActors.length(); i++) {
			Actor* a = knownActors.get(i);
			cout << "- " << a->getName() << endl;  // Assuming Actor has getName()
		}
	}
}