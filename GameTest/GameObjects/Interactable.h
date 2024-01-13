#pragma once
class World;

class Interactable
{
public:
	virtual void OnInteractWithPlayer(World& world) = 0;
};

