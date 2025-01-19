#include "../../include/Models/Movie.h"

#include <iostream>

Movie::Movie() : id(0), name(""), plot(""), year(0) { }

Movie::Movie(uint32_t id, std::string name, std::string plot, uint16_t year) 
	: id(id)
	, name(name)
	, plot(plot)
	, year(year) { }

void Movie::print() {
	std::cout << "[MOVIE]"
		<< "\nID: " << id
		<< "\nName: " << name
		<< "\nPlot: " << plot
		<< "\nYear: " << year
		<< std::endl;
}
