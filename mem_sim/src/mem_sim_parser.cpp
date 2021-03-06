
#include <iostream>
#include <string>
#include <sstream>
#include "mem_sim_parser.h"
#include "mem_sim_exceptions.h"


Parser::Parser()
{
}


Parser::~Parser()
{
}


std::vector<std::string> Parser::parse(std::string inputString)
{
	std::vector <std::string> result;
	result = tokenize(inputString);
	if (result[0] != "read-req" &&
		result[0] != "write-req" &&
		result[0] != "flush-req" &&
		result[0] != "debug-req" &&
		result[0][0] != '#' &&
		result[0] != "EOF"
		)
	{
		std::stringstream ss;
		ss << "#Error: Unknown input: ";
		ss << inputString;
		throw invalidInputException(ss.str().c_str());
	}
	return result;
}

std::vector<std::string> Parser::tokenize(std::string inputString)
{
	std::vector<std::string> result;
	unsigned begin = 0;
	unsigned end = 0;
	while (begin < inputString.length() && end < inputString.length())
	{
		end = inputString.find(' ', begin);
		if (end == begin)
			end = inputString.find('\n', begin);
		result.push_back(inputString.substr(begin, end - begin));
		begin = end+1;
	}
	return result;
}
