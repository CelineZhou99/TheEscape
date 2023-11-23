//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "Actor.h"
#include "Scene.h"
//------------------------------------------------------------------------
Actor* player;
std::vector<Actor*> actors;
std::vector<GameObject*> game_objects;
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	player = new Actor(new Renderer(".\\Images\\Player.bmp", 1, 1, 400.0f, 400.0f), 400.0f, 400.0f, TagType::PLAYER);
	float speed = 1.0f / 8.0f;
	player->GetRenderer()->CreateSpriteAnimation(speed, { 0,1,2,3 }, { 4,5,6,7 }, { 8,9,10,11 }, { 12,13,14,15 });

	Scene scene;
	scene.LoadMap(".\\SceneData\\TestMap2.txt", &actors, &game_objects);

}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	if (!player) { return; }
	player->GetRenderer()->UpdateSprite(deltaTime);
	//------------------------------------------------------------------------
	// Handle player movement
	//------------------------------------------------------------------------
	BoxCollider collider = BoxCollider(*player->GetCollider()); 
	FacingDirection direction = FacingDirection::NONE;
	float player_move_by_x = 0;
	float player_move_by_y = 0;

	if (App::IsKeyPressed('W'))
	{
		collider.MoveColliderPosition(0, 1);
		direction = FacingDirection::UP;
		player_move_by_y = PLAYER_MOVE_BY;
	}
	else if (App::IsKeyPressed('S'))
	{
		collider.MoveColliderPosition(0, -1);
		direction = FacingDirection::DOWN;
		player_move_by_y = -PLAYER_MOVE_BY;
	}
	else if (App::IsKeyPressed('A'))
	{
		collider.MoveColliderPosition(-1, 0);
		direction = FacingDirection::LEFT;
		player_move_by_x = -PLAYER_MOVE_BY;
	}
	else if (App::IsKeyPressed('D'))
	{
		collider.MoveColliderPosition(1, 0);
		direction = FacingDirection::RIGHT;
		player_move_by_x = PLAYER_MOVE_BY;
	}
	bool should_move = true;
	
	for (Actor* actor : actors)
	{
		if (player->GetCollider()->CheckCollision(&collider, actor->GetCollider()))
		{
			if (actor->GetTag() == TagType::MOVABLE_OBJECT)
			{
				float move_by_x = 0;
				float move_by_y = 0;
				switch (direction)
				{
				case FacingDirection::UP:
					move_by_y = MOVABLE_OBJECT_MOVE_BY;
					break;
				case FacingDirection::DOWN:
					move_by_y = -MOVABLE_OBJECT_MOVE_BY;
					break;
				case FacingDirection::LEFT:
					move_by_x = -MOVABLE_OBJECT_MOVE_BY;
					break;
				case FacingDirection::RIGHT:
					move_by_x = MOVABLE_OBJECT_MOVE_BY;
					break;
				}
				// make that actor move in the opposite direction of the player
				actor->UpdateActorPosition(move_by_x, move_by_y);
			}
			should_move = false;
		}
	}
	if (should_move)
	{
		player->UpdateAnimatedActorPosition(player_move_by_x, player_move_by_y, direction);
	}

	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav");
	}
	
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	

	for (GameObject* actor : game_objects)
	{
		actor->GetRenderer()->DrawSprite();
	}

	for (Actor* actor : actors)
	{
		actor->GetRenderer()->DrawSprite();
	}

	player->GetRenderer()->DrawSprite();
	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(100, 100, "Sample Text");
	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	/*static float a = 0.0f;
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		float sx = 200 + sinf(a + i * 0.1f)*60.0f;
		float sy = 200 + cosf(a + i * 0.1f)*60.0f;
		float ex = 700 - sinf(a + i * 0.1f)*60.0f;
		float ey = 700 - cosf(a + i * 0.1f)*60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey,r,g,b);
	}*/
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	delete player;
	for (Actor* actor : actors)
	{
		delete actor;
	}
	for (GameObject* actor : game_objects)
	{
		delete actor;
	}
}