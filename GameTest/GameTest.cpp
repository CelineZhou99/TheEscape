//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include "World.h"
//------------------------------------------------------------------------
#include <chrono>
#include <thread>
//------------------------------------------------------------------------
std::unique_ptr<World> world;
bool is_space_pressed = false;
bool is_restart_pressed = false;
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	world = std::make_unique<World>();
	world->Init();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	if (!world->has_game_ended)
	{
		if (!world->text_box.GetIsDialogueFinished())
		{
			if (App::IsKeyPressed(VK_SPACE) && !is_space_pressed)
			{
				is_space_pressed = true;
			}
			if (!App::IsKeyPressed(VK_SPACE) && is_space_pressed)
			{
				is_space_pressed = false;
				world->text_box.NextDialogue();
			}
		}
		world->Update(deltaTime);
	}
	else
	{
		if (App::IsKeyPressed('R') && !is_restart_pressed)
		{
			is_restart_pressed = true;
		}
		if (!App::IsKeyPressed('R') && is_restart_pressed)
		{
			is_restart_pressed = false;
			world->has_game_ended = false;
			world->Init();
		}
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	if (!world->has_game_ended)
	{
		world->DrawAllSprites();
		world->DrawUI();
		
		if (!world->text_box.GetIsDialogueFinished())
		{
			world->DrawTextBox();
		}
	}
	else 
	{
		world->end_screen_sprite->Draw();
	}
	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	/*App::Print(100, 100, "Sample Text");*/
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
}