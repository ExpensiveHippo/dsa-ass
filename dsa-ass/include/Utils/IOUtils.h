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
@brief Get a validated uint16_t from the user

@param prompt - The prompt to display to the user
@param i - The uint16_t to store the validated input
@param abort - Allow user to quit by entering command to quit (default ":q")

@return bool - False if process was aborted
*/
bool getValidatedUint16(std::string prompt, uint16_t& i, bool abort = true);


/*
@brief Get a validated uint32_t from the user

@param prompt - The prompt to display to the user
@param i - The uint32_t to store the validated input
@param abort - Allow user to quit by entering command to quit (default ":q")

@return bool - False if process was aborted
*/
bool getValidatedUint32(std::string prompt, uint32_t& i, bool abort = true);

