#pragma once

class Scene;

class HealthComponent
{
public:
	HealthComponent(short max_health) : _max_health(max_health), _curr_health(max_health) {}
	short GetHealth() const { return _curr_health; }
	void TakeDamage() { --_curr_health; }
	bool IsDead();

protected:
	short _max_health;
	short _curr_health;
};

