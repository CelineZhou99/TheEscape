#include "stdafx.h"
#include "Blackboard.h"
#include <cassert>

any_type_ptr Blackboard::GetVariable(std::string name)
{
    blackboard_map::iterator it = _blackboard_variables.find(name);
    if (it != _blackboard_variables.end())
    {
        return it->second;
    }
    assert(true && it == _blackboard_variables.end());
    return nullptr;
}

void Blackboard::SetVariable(std::string name, AnyType* value)
{
    _blackboard_variables[name] = std::make_shared<AnyType>(*value);
}

std::shared_ptr<Vector2D> Blackboard::GetVectorVariable(std::string name)
{
    temp_map::iterator it = _temp_variables.find(name);
    if (it != _temp_variables.end())
    {
        return it->second;
    }
    return nullptr;
}

void Blackboard::SetVectorVariable(std::string name, Vector2D& vector)
{
    _temp_variables[name] = std::make_shared<Vector2D>(vector);
}

void Blackboard::RemoveVectorVariable(std::string name)
{
    _temp_variables.erase(name);
}

FacingDirection Blackboard::GetDirectionVariable(std::string name)
{
    temp_map_direction::iterator it = _temp_direction_variables.find(name);
    if (it != _temp_direction_variables.end())
    {
        return it->second;
    }
    return FacingDirection::NONE;
}

void Blackboard::SetDirectionVariable(std::string name, FacingDirection direction)
{
    _temp_direction_variables[name] = direction;
}

void Blackboard::RemoveDirectionVariable(std::string name)
{
    _temp_direction_variables.erase(name);
}
