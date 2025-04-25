#pragma once
#include <SDL3/SDL.h>

class Paddle {
public:
	Paddle(int x, int y, int width, int height, float speed);
	void handleInput();
	void update(int screenWidth);
	void render(SDL_Renderer* renderer);

	SDL_FRect getBounds() const;

private:
	SDL_FRect rect;
	float speed;
};