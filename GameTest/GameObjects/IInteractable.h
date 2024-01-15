#pragma once
class World;

class IInteractable
{
public:
	virtual void OnInteractWithPlayer(World& world) = 0;
};

