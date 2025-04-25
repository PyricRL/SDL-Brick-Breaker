#include "paddle.h"
#include <iostream>

// Paddle constructer
// Assigns speed from the constructer to the private speed variable
Paddle::Paddle(int x, int y, int width, int height, float speed)
	: speed(speed)
{
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
}

void Paddle::handleInput() {
	auto currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_A]) {
		rect.x -= speed;
	}
	if (currentKeyStates[SDL_SCANCODE_D]) {
		rect.x += speed;
	}
}

void Paddle::update(int screenWidth) {
	if (rect.x < 0) {
		rect.x = 0;
	}
	if (rect.x + rect.w > screenWidth) {
		rect.x = screenWidth - rect.w;
	}
}

void Paddle::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

SDL_FRect Paddle::getBounds() const {
	return rect;
}