#include "stdafx.h"
#include "IEnemy.h"

void IEnemy::TakeDamage()
{
	--_curr_health;
}
