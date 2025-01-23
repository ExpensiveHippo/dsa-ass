#include "../../include/Utils/StringUtils.h"

Vector<std::string> split(std::string s, std::string delimiter) {
	// track position of string seen
	size_t pos; 
	size_t len = delimiter.length();
	std::string token;
	Vector<std::string> tokens; 
	
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		tokens.push(token);
		s.erase(0, pos + len);
	}
	tokens.push(s);
	
	return tokens;
}

std::string replace(std::string s, std::string oldStr, std::string newStr) {
	// track position of string seen
	size_t pos; 

	// if newStr is empty, replace with empty string
	size_t len = newStr.length() > 0 ? newStr.length() : 1;
	
	while ((pos = s.find(oldStr)) != std::string::npos) {
		s.replace(pos, len, newStr);
	}

	return s;
}

bool isValidUInt(const std::string& s) {
	
	// returns false if empty or negative
	if (s.empty() || s[0] == '-') {
		return false;
	}

	try {

		// store number of characters processed
		size_t pos; 

		unsigned long result = std::stoul(s, &pos);

		// return false if the conversion was not completed for the entire string
		if (pos != s.length()) {
			return false;
		}

		// check if in bounds
		if (result > std::numeric_limits<int>::max()) {
			return false;
		}

		return true;
	}
	catch (const std::exception&) {
		return false;
	}
}
