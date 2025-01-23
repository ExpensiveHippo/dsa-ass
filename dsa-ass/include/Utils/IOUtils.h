#pragma once

#include <string>

const std::string QUITCOMMAND = ":q";

/*
@brief Get a validated (not empty) string from the user

@param prompt - The prompt to display to the user
@param s - The string to store the validated input
@param abort - Allow user to quit by entering command to quit (default ":q")

@return void
*/
bool getValidatedString(std::string prompt, std::string& s, bool abort = true);

/*
@brief Get a validated int from the user

@param prompt - The prompt to display to the user
@param i - The int to store the validated input
@param abort - Allow user to quit by entering command to quit (default ":q")

@return bool - False if process was aborted
*/
bool getValidatedUInt(std::string prompt, int& i, bool abort = true);


