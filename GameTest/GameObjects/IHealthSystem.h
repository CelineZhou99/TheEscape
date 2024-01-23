#pragma once

class Scene;

class IHealthSystem
{
public:
	void SetMaxHealth(short health) { _max_health = health; _curr_health = _max_health; }
	short GetHealth() { return _curr_health; }
	virtual void TakeDamage() = 0;
	bool IsDead();
	virtual void OnDeath(Scene* scene) = 0;

protected:
	short _max_health = 0;
	short _curr_health = 0;
};

