#pragma once
#include <unordered_map>
#include <string>
#include "../GameObjects/Vector2D.h"
#include "../GameObjects/Renderer.h"
#include <memory>

class AnyType {};

template<class T>
class Any : public AnyType
{
public:
	Any() {}
	Any(const T& data) : _data(data) {}

	T& GetData() { return _data; }

private:
	T _data;
};

using blackboard_map = std::unordered_map<std::string, std::shared_ptr<AnyType>>;
using any_type_ptr = std::shared_ptr<AnyType>;

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

