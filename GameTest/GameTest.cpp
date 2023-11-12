//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <sstream>
#include <string>
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "Actor.h"
#include "Player.h"
//------------------------------------------------------------------------
Player* player;
Player* square;
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	player = new Player(".\\TestData\\square.bmp", 1, 1, 400.0f, 400.0f);
	if (player)
	{
		float speed = 1.0f / 8.0f;
		player->GetRenderer()->CreateSpriteAnimation(speed, { 0,1,2,3,4,5,6,7 }, { 8,9,10,11,12,13,14,15 }, { 16,17,18,19,20,21,22,23 }, { 24,25,26,27,28,29,30,31 });
	}
	square = new Player(".\\TestData\\square.bmp", 1, 1, 500.0f, 500.0f);
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
	float x = player->GetCollider()->GetPosition()->X();
	float y = player->GetCollider()->GetPosition()->Y();
	Vector2D* new_pos = new Vector2D(x, y);
	BoxCollider* collider = new BoxCollider(new_pos, player->GetCollider()->GetWidth(), player->GetCollider()->GetHeight());
	// ASK ABOUT WHY THIS DOESN'T WORK
	// BoxCollider* collider = new BoxCollider(*player->GetCollider()); 

	if (App::IsKeyPressed('W'))
	{
		collider->UpdatePosition(0, 1);

		if (!player->GetCollider()->CheckCollision(collider, square->GetCollider()))
		{
			player->GetRenderer()->SetAnimation(FacingDirection::UP);
			player->GetCollider()->UpdatePosition(0, 1);
		}
	}
	else if (App::IsKeyPressed('S'))
	{
		collider->UpdatePosition(0, -1);

		if (!player->GetCollider()->CheckCollision(collider, square->GetCollider()))
		{
			player->GetRenderer()->SetAnimation(FacingDirection::DOWN);
			player->GetCollider()->UpdatePosition(0, -1);
		}
	}
	else if (App::IsKeyPressed('A'))
	{
		collider->UpdatePosition(-1, 0);

		if (!player->GetCollider()->CheckCollision(collider, square->GetCollider()))
		{
			player->GetRenderer()->SetAnimation(FacingDirection::LEFT);
			player->GetCollider()->UpdatePosition(-1, 0);
		}
	}
	else if (App::IsKeyPressed('D'))
	{
		collider->UpdatePosition(1, 0);

		if (!player->GetCollider()->CheckCollision(collider, square->GetCollider()))
		{
			player->GetRenderer()->SetAnimation(FacingDirection::RIGHT);
			player->GetCollider()->UpdatePosition(1, 0);
		}
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
	square->GetRenderer()->DrawSprite();
	if (!player) { return; }
	player->GetRenderer()->DrawSprite();

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	App::Print(100, 100, "Sample Text");
	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	static float a = 0.0f;
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
	}
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	delete player;
	delete square;
}