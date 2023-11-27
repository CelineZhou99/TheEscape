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
World* world;
//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	world = new World();
	world->Init();
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	if (!world->player) { return; }
	world->player->GetRenderer()->UpdateSprite(deltaTime);
	//------------------------------------------------------------------------
	// Handle player movement
	//------------------------------------------------------------------------
	BoxCollider collider = BoxCollider(*world->player->GetCollider());
	FacingDirection direction = FacingDirection::NONE;
	float player_move_by_x = 0;
	float player_move_by_y = 0;

	world->CalculateNextPlayerMovement(collider, direction, player_move_by_x, player_move_by_y);

	if (world->ShouldPlayerMove(collider, direction))
	{
		world->player_controller->UpdatePlayerPosition(player_move_by_x, player_move_by_y, direction);
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	for (GameObject* actor : world->game_objects)
	{
		actor->GetRenderer()->DrawSprite();
	}

	for (Actor* actor : world->actors)
	{
		actor->GetRenderer()->DrawSprite();
	}

	world->player->GetRenderer()->DrawSprite();
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
	delete world;
}