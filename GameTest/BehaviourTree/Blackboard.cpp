#include "stdafx.h"
#include "Blackboard.h"

any_type_ptr Blackboard::GetVariable(std::string name)
{
    blackboard_map::iterator it = _blackboard_variables.find(name);
    if (it != _blackboard_variables.end())
    {
        return it->second;
    }
    return nullptr;
}

void Blackboard::SetVariable(std::string name, AnyType* value)
{
    _blackboard_variables[name] = std::shared_ptr<AnyType>(value);
}

void Blackboard::RemoveVariable(std::string name)
{
    _blackboard_variables.erase(name);
}