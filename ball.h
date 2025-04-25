#pragma once
#include <SDL3/SDL.h>
#include "paddle.h"
#include "blockHandler.h"
#include "player.h"

class Ball {
public:
	Ball(int x, int y, int radius, float xVel, float yVel);
	void update(int screenWidth, int screenHeight, Paddle& paddle, BlockHandler& blockHandler, Player& player);
	void render(SDL_Renderer* renderer);

	void restart(int screenWidth, int screenHeight);

	SDL_FRect getBounds() const;

private:
	SDL_FRect rect;
	float xVel;
	float yVel;
};