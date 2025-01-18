#pragma once

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
};

