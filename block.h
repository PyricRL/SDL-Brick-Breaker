#pragma once
#include <SDL3/SDL.h>

class Block {
public:
	Block(int x, int y, int width, int height, int health);
	void explode();
	void render(SDL_Renderer* renderer);

	bool isDestroyed();

	int getHealth();
	void setHealth(int h);

	const SDL_FRect& getBounds() const;

private:
	SDL_FRect rect;
	int health;
	Uint8 alpha;
	bool destroyed;
};