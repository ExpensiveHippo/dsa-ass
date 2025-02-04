#include "../include/Init.h"
#include "../include/Utils/StringUtils.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>


Vector<Vector<std::string>> parseCSVFile(std::string filepath, bool removeHeader) {
	std::ifstream file(filepath);

	if (!file.is_open()) {
		throw std::ios_base::failure("Unable to open file " + filepath);
	}

	Vector<Vector<std::string>> result;
	std::string line;
	
	if (removeHeader) {
		std::getline(file, line);
	}

	while (std::getline(file, line)) {
		Vector<std::string> fields;
		std::stringstream ss(line);
		std::string field;
		std::string temp;
		bool ignore = false;

		while (std::getline(ss, temp, ',')) {

			// if start of token is '"', don't add token to vector immediately.
			// collect token until '"' is right before a comma
			if (temp.front() == '"' && !ignore) {
				ignore = true;
				field = temp;
			}
			else if (ignore) {
				field += "," + temp;
				if (temp.back() == '"') {
					ignore = false;
					// don't include outer quotes
					fields.push(temp.substr(1, temp.length() - 2));
				}
			}
			else {
				fields.push(temp);
			}
		}
		result.push(std::move(fields));
	}
	file.close();
	return result;
}

Vector<Movie*> initMovies() {
	Vector<Movie*> movies;

	try {
		Vector<Vector<std::string>> data = parseCSVFile(MOVIES_FILE);
		for (int i = 0; i < data.length(); i++) {
			Vector<std::string> fields = data.get(i);
			if (fields.length() != 4) {
				std::cout << "[WARNING] Fields do not match. Skipping [" << i << "]\n";
				continue;
			}

			Movie* m = new Movie(
				std::stoi(fields.get(0)),
				fields.get(1),
				fields.get(2),
				std::stoi(fields.get(3))
			);
			movies.push(m);
		}
	} catch (std::exception& err) {
		std::cerr << "[ERROR] Error initialising movies: " << err.what() << std::endl;
	}

	return movies;
};

Vector<Actor*> initActors() {
	std::ifstream file(ACTORS_FILE);
	std::string line;
	Vector<Actor*> actors;

	std::getline(file, line); // get rid of headers

	while (std::getline(file, line)) {
		Vector<std::string> data = split(line, ",");
		Actor* a = new Actor(
			std::stoi(data.get(0)),
			replace(data.get(1), "\"", ""),
			std::stoi(data.get(2))
		);
		actors.push(a);
	}
	file.close();

	return actors;
};
