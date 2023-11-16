//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <sstream>
#include <string>
#include <fstream>
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "Actor.h"
#include "SquareActor.h"
//------------------------------------------------------------------------
SquareActor* player;
std::vector<SquareActor*> square_actors;
std::map<float, Vector2D> test_map;
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	player = new SquareActor(".\\Images\\Player.bmp", 1, 1, 400.0f, 400.0f, TagType::PLAYER);
	float speed = 1.0f / 8.0f;
	player->GetRenderer().CreateSpriteAnimation(speed, { 0,1,2,3 }, { 4,5,6,7 }, { 8,9,10,11 }, { 12,13,14,15 });

	std::ifstream infile(".\\SceneData\\TestMap.txt");
	float x, y;
	while (infile >> x >> y)
	{
		SquareActor* actor = new SquareActor(".\\Images\\Brick.bmp", 1, 1, x, y, TagType::STATIC_OBJECT);
		square_actors.push_back(actor);
	}

	SquareActor* box = new SquareActor(".\\Images\\Box.bmp", 1, 1, 500.f, 600.f, TagType::MOVABLE_OBJECT);
	square_actors.push_back(box);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	if (!player) { return; }
	player->GetRenderer().UpdateSprite(deltaTime);
	//------------------------------------------------------------------------
	// Handle player movement
	//------------------------------------------------------------------------
	BoxCollider collider = BoxCollider(*player->GetCollider()); 
	FacingDirection direction = FacingDirection::NONE;
	float move_to_x = 0;
	float move_to_y = 0;

	if (App::IsKeyPressed('W'))
	{
		collider.UpdatePosition(0, 1);
		direction = FacingDirection::UP;
		move_to_y = 1;
	}
	else if (App::IsKeyPressed('S'))
	{
		collider.UpdatePosition(0, -1);
		direction = FacingDirection::DOWN;
		move_to_y = -1;
	}
	else if (App::IsKeyPressed('A'))
	{
		collider.UpdatePosition(-1, 0);
		direction = FacingDirection::LEFT;
		move_to_x = -1;
	}
	else if (App::IsKeyPressed('D'))
	{
		collider.UpdatePosition(1, 0);
		direction = FacingDirection::RIGHT;
		move_to_x = 1;
	}
	bool should_move = true;
	
	for (SquareActor* actor : square_actors)
	{
		if (player->GetCollider()->CheckCollision(&collider, actor->GetCollider()))
		{
			if (actor->GetTag() == TagType::MOVABLE_OBJECT)
			{
				float x_direction = actor->GetTransform().X() - player->GetTransform().X() > 0 ? 1 : -1;
				float y_direction = actor->GetTransform().Y() - player->GetTransform().Y() > 0 ? 1 : -1;
				x_direction *= 5;
				y_direction *= 5;
				// make that actor move in the opposite direction of the player
			}
			should_move = false;
		}
	}
	if (should_move)
	{
		player->GetRenderer().SetAnimation(direction);
		player->GetCollider()->UpdatePosition(move_to_x, move_to_y);
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
	if (!player) { return; }
	player->GetRenderer().DrawSprite();

	for (SquareActor* actor : square_actors)
	{
		actor->GetRenderer().DrawSprite();
	}
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
	player->CleanUp();
	delete player;
	for (SquareActor* actor : square_actors)
	{
		actor->CleanUp();
		delete actor;
	}
}