#include "stdafx.h"
#include "BoxCollider.h"

#include <windows.h> 
#include <sstream>
#include <string>

bool BoxCollider::CheckCollision(Collider& obj_1_collider, Collider& obj_2_collider)
{
    // use AABB collision detection
    float obj_1_top_left_x = obj_1_collider.GetPosition().X();
    float obj_1_top_left_y = obj_1_collider.GetPosition().Y();
    float obj_1_bot_right_x = obj_1_collider.GetPosition().X() + obj_1_collider.GetWidth();
    float obj_1_bot_right_y = obj_1_collider.GetPosition().Y() - obj_1_collider.GetHeight();

    float obj_2_top_left_x = obj_2_collider.GetPosition().X();
    float obj_2_top_left_y = obj_2_collider.GetPosition().Y();
    float obj_2_bot_right_x = obj_2_collider.GetPosition().X() + obj_2_collider.GetWidth();
    float obj_2_bot_right_y = obj_2_collider.GetPosition().Y() - obj_2_collider.GetHeight();

    bool x_axis_collision = (obj_1_bot_right_x > obj_2_top_left_x) && (obj_2_bot_right_x > obj_1_top_left_x);
    bool y_axis_collision = (obj_1_top_left_y > obj_2_bot_right_y) && (obj_2_top_left_y > obj_1_bot_right_y);

    return x_axis_collision && y_axis_collision;
}
