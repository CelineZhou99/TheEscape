#pragma once
#include <unordered_map>
#include <string>

class AnyType {};

template<class T>
class Any : public AnyType
{
public:
	Any() {}
	Any(const T& data) : _data(data) {}

	T& GetData() { return _data; }

	bool operator == (const Any& any)
	{
		if (_data == any)
			return true;
		return false;
	}

private:
	T _data;
};

using any_type_ptr = std::shared_ptr<AnyType>;
using blackboard_map = std::unordered_map<std::string, any_type_ptr>;

class Blackboard
{
public:
	Blackboard() : _blackboard_variables({}) {}

	// this class can hold different types of variables for the behaviour tree
	// e.g. bool, int, float
	any_type_ptr GetVariable(std::string name);
	void SetVariable(std::string name, AnyType* value);
	void RemoveVariable(std::string name);

private:
	blackboard_map _blackboard_variables;
};

