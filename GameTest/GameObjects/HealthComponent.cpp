#include "stdafx.h"
#include "HealthComponent.h"

bool HealthComponent::IsDead()
{
    return _curr_health <= 0 ? true : false;
}
