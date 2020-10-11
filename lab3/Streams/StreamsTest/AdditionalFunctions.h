#include "stdafx.h"

inline std::string GetStringFromStream(std::string const& fileName)
{
	std::ifstream istream;
	istream.open(fileName, std::ios::binary);
	std::string a = std::string((std::istreambuf_iterator<char>(istream)), (std::istreambuf_iterator<char>()));
	return a;
}