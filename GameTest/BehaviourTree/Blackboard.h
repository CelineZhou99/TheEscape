#pragma once
#include <unordered_map>
#include <string>

using bool_map = std::unordered_map<std::string, bool>;

class Blackboard
{
public:
	Blackboard() : _bool_variables({}) {}

	// this class can hold different types of variables for the behaviour tree
	// e.g. bool, int, float
	bool GetBoolVariable(std::string name);
	void SetBoolVariable(std::string name, bool value);

private:
	std::unordered_map<std::string, bool> _bool_variables;
};

