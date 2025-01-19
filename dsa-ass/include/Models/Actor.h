#pragma once

#include <cstdint>
#include <string>

class Actor
{
private:
	uint32_t id;
	std::string name;
	uint16_t birthYear;
public:
	Actor();
	Actor(uint32_t id, std::string name, uint16_t birthYear);
	void print();
};

