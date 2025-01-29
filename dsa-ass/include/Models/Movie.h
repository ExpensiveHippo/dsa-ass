#pragma once
#include <iostream>
#include <string>
#include <cstdint>

class Movie
{
private:
	uint32_t id;
	std::string name;
	std::string plot;
	uint16_t year;

public:
	// default constructor 
	Movie();
	Movie(uint32_t id, std::string name, std::string plot, uint16_t year);
	void print();
	uint16_t getReleaseYear();
	bool operator<(const Movie& other) const;
	bool operator>(const Movie& other) const;

};

