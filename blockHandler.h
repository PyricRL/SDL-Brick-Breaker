#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "block.h"

class BlockHandler {
public:
	void generateBlocks(int rows, int columns, int blockWidth, int blockHeight, int screenWidth, int screenHeight);
	void render(SDL_Renderer* renderer);
	void removeBlocks();

	std::vector<Block>& getBlocks();

private:
	std::vector<Block> blocks;
};