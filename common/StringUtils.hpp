//============================================================================
// Name        : StringUtils.hpp
// Author      : Diego Viqueira
// Version     :
// Copyright   :
// Description : Helpers for Strings
//============================================================================

#ifndef STRING_UTILS_HPP_
#define STRING_UTILS_HPP_

#include <sstream>
#include <cstdint>
#include <vector>


namespace str {

	//Split a String 
	std::vector<std::string> split(const std::string& str, const std::string& delim)
	{
		std::vector<std::string> tokens;
		size_t prev = 0, pos = 0;
		do
		{
			pos = str.find(delim, prev);
			if (pos == std::string::npos) pos = str.length();
			std::string token = str.substr(prev, pos-prev);
			if (!token.empty()) tokens.push_back(token);
			prev = pos + delim.length();
		}
		while (pos < str.length() && prev < str.length());
		return tokens;
	}

}	// str namespace


#endif		/*	STRING_UTILS_HPP_	*/




