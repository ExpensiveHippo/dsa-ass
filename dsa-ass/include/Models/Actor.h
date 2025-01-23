#pragma once

#include <cstdint>
#include <string>

class Actor
{
private:
	int id;
	std::string name;
	int birthYear;
public:
	Actor();
	Actor(int id, std::string name, int birthYear);
	int getId();
	void setName(std::string name);
	std::string getName();
	void setBirthYear(int birthYear);
	int getBirthYear();
	void print();
};

