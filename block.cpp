#include "block.h"
#include <iostream>

Block::Block(int x, int y, int width, int height, int health)
	: health(health), alpha(255), destroyed(false)
{
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
}

void Block::explode() {
	while (alpha > 0) {
		alpha -= 1;
	}
	destroyed = true;
}

void Block::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	if (health == 1) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
	}
	else if (health == 2) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, alpha);
	}
	else if (health == 3) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, alpha);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, alpha);
	}
	SDL_RenderFillRect(renderer, &rect);
}

bool Block::isDestroyed() {
	return destroyed;
}

int Block::getHealth() {
	return health;
}

void Block::setHealth(int h) {
	Block::health = h;
}

const SDL_FRect& Block::getBounds() const {
	return rect;
}