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

	T GetData() { return _data; }

private:
	T _data;
};

using blackboard_map = std::unordered_map<std::string, std::shared_ptr<AnyType>>;
using any_type = std::shared_ptr<AnyType>;

// TODO: remove after template class is fixed
using temp_map = std::unordered_map<std::string, std::shared_ptr<Vector2D>>;
using temp_map_direction = std::unordered_map<std::string, FacingDirection>;

class Blackboard
{
public:
	Blackboard() : _blackboard_variables({}) {}

	// this class can hold different types of variables for the behaviour tree
	// e.g. bool, int, float
	any_type GetVariable(std::string name);
	void SetVariable(std::string name, AnyType& value);

	// TODO: remove after template class is fixed 
	std::shared_ptr<Vector2D> GetVectorVariable(std::string name);
	void SetVectorVariable(std::string name, Vector2D& vector);
	void RemoveVectorVariable(std::string name);
	FacingDirection GetDirectionVariable(std::string name);
	void SetDirectionVariable(std::string name, FacingDirection direction);
	void RemoveDirectionVariable(std::string name);

private:
	blackboard_map _blackboard_variables;

	// TODO: remove after template class is fixed
	temp_map _temp_variables;
	temp_map_direction _temp_direction_variables;
};

