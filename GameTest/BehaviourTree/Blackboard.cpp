#include "stdafx.h"
#include "Blackboard.h"
#include <cassert>

bool Blackboard::GetBoolVariable(std::string name)
{
    bool_map::iterator it = _bool_variables.find(name);
    if (it != _bool_variables.end())
    {
        return it->second;
    }
    assert(true && it == _bool_variables.end());
    return false;
}

void Blackboard::SetBoolVariable(std::string name, bool value)
{
    _bool_variables[name] = value;
}
