#pragma once
#include <string>
#include <sstream>

inline std::string GetToStringExpectedOutput(std::string const& expectedInvertoryString,
	std::string const& expectedStateString, unsigned expectedQuarterCount)
{
	std::stringstream ss;

	ss << "\nMighty Gumball, Inc.\n" <<
		"C++-enabled Standing Gumball Model #2016 (with state)\n" <<
		"Inventory: " << expectedInvertoryString << "\n"
		"Quarters: " << expectedQuarterCount << "\n" <<
		"Machine is " << expectedStateString << "\n";

	return ss.str();
}