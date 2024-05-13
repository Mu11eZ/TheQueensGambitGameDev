#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
	//AABB = Axis Aligned Bounding Box
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

};