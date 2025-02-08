/*
* NAME: RYAN HO
* ID: S10261024
* GROUP: glorp
*/

#pragma once

#include "../DataStructures/Vector.h"

#include <string>

/*
@brief Splits a string based on the delimiter and returns the resulting vector

@param s - The original string
@param delimiter - The delimiter

@returns Vector<std::string> - The resulting tokens after splitting
*/
Vector<std::string> split(std::string s, std::string delimiter);

/*
@brief Replaces every occurence of a substring in a string with a new string

@param s - The original string
@param oldSr - The substring to replace
@param newStr - The new string to replace with

@returns std::string - The resulting string after replacement
*/
std::string replace(std::string s, std::string oldStr, std::string newStr);

/*
@brief Check if string can be converted to int 

@param s - The string to check

@return bool - True if the string can be converted to uint16_t, false otherwise
*/
bool isValidUInt(const std::string& s);
