#pragma once
#include <iostream>
#include <time.h>
#include "../../include/Utils/IOUtils.h"
#include "../../include/Models/User.h"


User::User() {}
template <typename T>
using CompareFunction = bool(*)(T*, T*);	//function pointer to compare two different pointer objects (actors,movies)
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
bool compareActorsByYear(Actor* a1, Actor* a2) {
	return a1->getBirthYear() >= a2->getBirthYear();
}
bool compareMoviesByYear(Movie* m1, Movie* m2) {
	return m1->getYear() <= m2->getYear();
}
bool compareActorsByRating(Actor* a1, Actor* a2) {
	return a1->getRating() >= a2->getRating();
}
bool compareMoviesByRating(Movie* m1, Movie* m2) {
	return m1->getRating() >= m2->getRating();
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
	AVLTree<Actor> filteredActors(compareActorsByYear);
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
		if (min >= max) {
			cout << "[ERROR] Please enter a valid age range (min < max)" << endl;
			continue;
		}
		break;
	}
	for (int i = 0; i < actors.length(); i++) {
		int age = currentYear - actors.get(i)->getBirthYear();	
		if (age >= min && age <= max) {
			filteredActors.push(actors.get(i));
		}
	}
	cout << "\n\n";
	filteredActors.displayInOrder();
}
void User::displayRecentMovies(Vector<Movie*>& movies) {
	AVLTree<Movie> recentMovies(compareMoviesByYear);
	for (int i = 0; i < movies.length(); i++) {
		int currentYear = getCurrentYear();
		int releaseYear = movies.get(i)->getYear();
		if (releaseYear <= currentYear && releaseYear >= currentYear - 3) {
			recentMovies.push(movies.get(i));
		}
	}
	cout << "\n\n";
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
		if (!movies.hasKey(movieName)) {
			cout << "[ERROR] Movie name: \"" << movieName << "\" does not exist" << endl;
			continue;
		}
		break;
	}

	Vector<Movie*> mVec = movies.get(movieName);
	Movie* movie = chooseMovie(mVec);
	Vector<Actor*> actors = movie->getActors();
	if (actors.length() == 0) {
		std::cout << "NO MOVIES\n";
		return;
	}
	
	if (actors.length() > 1) {
		int actorLength = static_cast<int>(actors.length());
		mergeSort<Actor>(actors, 0, actorLength - 1, (CompareFunction<Actor>)compareActorsByName);
	}
	cout << "\n\n";
	cout << "Actors in \"" << movieName << "\":" << endl;
	for (int i = 0; i < actors.length(); i++) {
		actors.get(i)->print();
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
		if (!actors.hasKey(actorName)) {
			cout << "[ERROR] Actor name: \"" << actorName << "\" not found" << endl;
			continue;
		}
		break;
	}

	Vector<Actor*> aVec = actors.get(actorName);
	Actor* actor = chooseActor(aVec);
	Vector<Movie*> movies = actor->getMovies();

	if (movies.length() == 0) {
		std::cout << "NO ACTORS\n";
		return;
	}

	if (movies.length() > 1) {
		int movieLength = static_cast<int>(movies.length());
		mergeSort<Movie>(movies, 0, movieLength - 1, (CompareFunction<Movie>)compareMoviesByName);
	}
	cout << "\n\n";
	cout << "Movies by \"" << actorName << "\":" << endl;
	for (int i = 0; i < movies.length(); i++) {
		movies.get(i)->print();
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
		if (!actors.hasKey(actorName)) {
			cout << "Actor name: \"" << actorName << "\" not found" << endl;
			continue;
		}
		break;
	}
	Vector<Actor*> actorVec = actors.get(actorName);
	Actor* actor = chooseActor(actorVec);

	//initialization for BFS
	Vector<Actor*> knownActors;
	HashMap<bool> visited; 
	Vector<Actor*> toVisit; 

	toVisit.push(actor);	//starts with the actor chosen by user
	visited.add(std::to_string(actor->getId()), true);	//mark chosen actor as visited

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
					if (coActor != actor && !visited.hasKey(std::to_string(coActor->getId()))) {
						knownActors.push(coActor);	//a standalone vector for displaying purposes.
						nextLevelActors.push(coActor);	//stores immediate actors to visit other known actors in the next level
						visited.add(std::to_string(coActor->getId()), true);
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
		cout << "\n\n";
		cout << "Actors known by " << actorName << ":" << endl;
		for (size_t i = 0; i < knownActors.length(); i++) {
			Actor* a = knownActors.get(i);
			a->print();
		}
	}
}
void User::displayActorsByRating(Vector<Actor*>& actors) {
	//initialization
	int actorLength = static_cast<int>(actors.length());
	AVLTree<Actor> filteredActors(compareActorsByRating);
	int minRating;
	bool isValid;
	while (true) {
		isValid = getValidatedUInt("Enter a minimum rating to filter actors (0-5 or \":q\" to quit): ", minRating);
		if (isValid) {
			return;
		}
		if (minRating < 0 || minRating > 5) {
			cout << "[ERROR] Rating must be between 0 and 5 inclusive" << endl;
			continue;
		}
		break;
	}
	bool hasActors = false;
	for (int i = 0; i < actors.length(); i++) {
		if (actors.get(i)->getRating() >= minRating) {
			filteredActors.push(actors.get(i));
			hasActors = true;
		}
	}
	if (!hasActors) {
		cout << "\nNo actors found with a rating greater than or equal to " << minRating << endl;
		return;
	}
	cout << "\n\n";
	filteredActors.displayInOrder();
}
void User::displayMoviesByRating(Vector<Movie*>& movies) {
	//initialization
	int movieLength = static_cast<int>(movies.length());
	AVLTree<Movie> filteredMovies(compareMoviesByRating);	//pass a comparator function
	int minRating;
	bool isValid;
	while (true) {
		isValid = getValidatedUInt("Enter a minimum rating to filter movies (0-5 or \":q\" to quit): ", minRating);
		if (isValid) {
			return;
		}
		else if (minRating < 0 || minRating > 5) {
			cout << "Rating must be between 0 and 5 inclusive" << endl;
			continue;
		}
		break;
	}
	bool hasMovies = false;

	for (int i = 0; i < movies.length(); i++) {
		if (movies.get(i)->getRating() >= minRating) {
			cout << "\n\n";
			filteredMovies.push(movies.get(i));
			hasMovies = true;
		}
	}
	if (!hasMovies) {
		cout << "No movies found with a rating greater than or equal to " << minRating << endl;
		return;
	}
	cout << "\n\n";
	filteredMovies.displayInOrder();
}
