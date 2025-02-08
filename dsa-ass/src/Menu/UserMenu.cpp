#include "../../include/Menu/UserMenu.h"
#include "../../include/Utils/IOUtils.h"

UserMenu::UserMenu(
	User& user,
	Vector<Actor*>& actorVector,
	Vector<Movie*>& movieVector,
	HashMap<Vector<Actor*>>& actorNameMap,
	HashMap<Vector<Movie*>>& movieNameMap,
	HashMap<Actor*>& actorIdMap,
	HashMap<Movie*>& movieIdMap
) :
	user(user),
	actorVector(actorVector),
	movieVector(movieVector),
	actorNameMap(actorNameMap),
	movieNameMap(movieNameMap),
	actorIdMap(actorIdMap),
	movieIdMap(movieIdMap) {}


void UserMenu::printUserMenu() {
	std::cout << "\n--------------USER MENU--------------" << std::endl;
	std::cout << "[0] Sign out" << std::endl;
	std::cout << "[1] Display actors' age (ascending)" << std::endl;
	std::cout << "[2] Display movies from last 3 years (ascending)" << std::endl;
	std::cout << "[3] Display movies an actor starred in (alphabetical)" << std::endl;
	std::cout << "[4] Display actors in that starred in movie (alphabetical)" << std::endl;
	std::cout << "[5] Display a list of actors a particular actor knows" << std::endl;
	std::cout << "[6] Add rating to actor" << std::endl;
	std::cout << "[7] Add rating to movie" << std::endl;
	std::cout << "[8] Display rating of actor" << std::endl;
	std::cout << "[9] Display rating of movie" << std::endl;
	std::cout << std::endl;
}


void UserMenu::handleUserChoice(int choice)
{
	switch (choice) {
	case 1:
		displayActorsByAge();
		break;
	case 2:
		displayRecentMovies();
		break;
	case 3:
		displayMoviesByActor();
		break;
	case 4:
		displayActorsByMovie();
		break;
	case 5:
		displayActorsKnown();
		break;
	case 6:
		addActorRating();
		break;
	case 7:
		addMovieRating();
		break;
	case 8:
		displayActorRating();
		break;
	case 9:
		displayMovieRating();
		break;
	default:
		break;
	}
}

void UserMenu::displayActorsByAge() {
	std::cout << "-------DISPLAYING ACTORS BY AGE---------\n";
	user.displayActorsByAge(actorVector);
}

void UserMenu::displayRecentMovies() {
	std::cout << "-------DISPLAYING RECENT MOVIES---------\n";
	user.displayRecentMovies(movieVector);
}

void UserMenu::displayMoviesByActor() {
	std::cout << "-------DISPLAYING MOVIES BY ACTOR---------\n";
	user.displayMoviesByActor(actorNameMap);
}

void UserMenu::displayActorsByMovie() {
	std::cout << "-------DISPLAYING ACTORS BY MOVIE---------\n";
	user.displayActorsByMovie(movieNameMap);
}

void UserMenu::displayActorsKnown() {
	std::cout << "-------DISPLAYING ACTORS KNOWN---------\n";
	user.displayActorsKnown(actorNameMap);
}

void UserMenu::addActorRating() {
	bool abort;
	std::string actorName;
	int rating;

	std::cout << "-------ADDING ACTOR RATING---------\n";

	do {
		abort = getValidatedString("Enter actor name (or \":q\" to quit): ", actorName);
		if (abort) {
			return;
		}

		if (!actorNameMap.hasKey(actorName)) {
			std::cout << "[ERROR] Actor \"" << actorName << "\" does not exist\n";
			continue;
		}

		Vector<Actor*> aVec = actorNameMap.get(actorName);
		Actor* a = chooseActor(aVec);

		std::cout << actorName << "'s current rating: " << a->getRating() << " (" << a->getTotalRatingCount() << ")" << std::endl;

		while (true) {
			abort = getValidatedUInt("Enter rating (0-5 or \":q\" to quit): ", rating);
			if (abort) {
				return;
			}
			try {
				a->addRating(rating);
				break;
			}
			catch (const std::out_of_range& err) {
				std::cout << "[ERROR] Rating must be between 0 - 5 inclusive." << "\n\n";
			}
		}

	} while (true);
}

void UserMenu::addMovieRating() {
	bool abort;
	std::string movieName;
	int rating;

	std::cout << "-------ADDING MOVIE RATING---------\n";

	do {
		abort = getValidatedString("Enter movie name (or \":q\" to quit): ", movieName);
		if (abort) {
			return;
		}

		if (!movieNameMap.hasKey(movieName)) {
			std::cout << "[ERROR] Movie\"" << movieName << "\" does not exist\n";
			continue;
		}

		Vector<Movie*> mVec = movieNameMap.get(movieName);
		Movie* m = chooseMovie(mVec);

		std::cout << movieName << "'s current rating: " << m->getRating() << " (" << m->getTotalRatingCount() << ")" << std::endl;

		while (true) {
			abort = getValidatedUInt("Enter rating (0-5 or \":q\" to quit): ", rating);
			if (abort) {
				return;
			}
			try {
				m->addRating(rating);
				std::cout << "[SUCCESS] Current movie rating is " << m->getRating() << " (" << m->getTotalRatingCount() << ")" << "\n\n";
				break;
			}
			catch (const std::out_of_range& err) {
				std::cout << "[ERROR] Rating must be between 0 - 5 inclusive." << "\n\n";
			}
		}
	} while (true);

}

void UserMenu::displayActorRating() {
	bool abort;
	std::string actorName;
	int rating;

	std::cout << "-------DISPLAYING ACTOR RATING---------\n";

	do {
		abort = getValidatedString("Enter actor name (or \":q\" to quit): ", actorName);
		if (abort) {
			return;
		}

		if (!actorNameMap.hasKey(actorName)) {
			std::cout << "[ERROR] Actor \"" << actorName << "\" does not exist\n";
			continue;
		}

		Vector<Actor*> aVec = actorNameMap.get(actorName);

		std::cout << "\n";

		for (int i = 0; i < aVec.length(); i++) {
			aVec.get(i)->print();
			std::cout << "\n";
		}
	
	} while (true);
}

void UserMenu::displayMovieRating() {
	bool abort;
	std::string movieName;

	std::cout << "-------DISPLAYING MOVIE RATING---------\n";

	do {
		abort = getValidatedString("Enter movie name (or \":q\" to quit): ", movieName);
		if (abort) {
			return;
		}

		if (!movieNameMap.hasKey(movieName)) {
			std::cout << "[ERROR] Movie \"" << movieName << "\" does not exist\n";
			continue;
		}

		Vector<Movie*> mVec = movieNameMap.get(movieName);

		std::cout << "\n";

		for (int i = 0; i < mVec.length(); i++) {
			mVec.get(i)->print();
			std::cout << "\n";
		}

	} while (true);

}

