#include "stdafx.h"
#include "GameObject.h"
#include "../Scenes/Scene.h"

void GameObject::Update(float deltaTime, Scene* scene)
{
	_renderer->UpdateSpriteAnimation(deltaTime);
}
