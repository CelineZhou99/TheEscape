#include "stdafx.h"
#include "IHealthSystem.h"

bool IHealthSystem::IsDead()
{
    return _curr_health <= 0 ? true : false;
}
