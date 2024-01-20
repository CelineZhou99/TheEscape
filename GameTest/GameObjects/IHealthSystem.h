#pragma once
class IHealthSystem
{
public:
	void SetMaxHealth(int health) { _max_health = health; _curr_health = _max_health; }
	int GetHealth() { return _curr_health; }
	virtual void TakeDamage() = 0;
	bool IsDead();

protected:
	int _max_health = 0;
	int _curr_health = 0;
};

