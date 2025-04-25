#include "blockHandler.h"
#include <iostream>

void BlockHandler::generateBlocks(int rows, int columns, int blockWidth, int blockHeight, int screenWidth, int screenHeight) {
	// Goals: 
	// Offset from top by set amount
	// Center across screen by dividing width and height by rows and columns
	// Add a gap (maybe auto)

	int margin = 25;

	int availableWidth	= screenWidth - (margin * 2);	// Adds 50 px margin between edges
	int availableHeight = (screenHeight / 2) - margin;	// keeps height at half

	// Compute the size of each cell
	int cellWidth  = availableWidth / columns;
	int cellHeight = availableHeight / rows;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			// Calculate the top-left corner of the *CELL* (relative to screen 0,0)
			int cellStartX = margin + (j * cellWidth);
			int cellStartY = margin + (i * cellHeight); // Start from top margin

			// Calculate the offset needed to center the *BLOCK* within its *CELL*
			// Integer division automatically floors the result.
			int offsetX = (cellWidth - blockWidth) / 2;
			int offsetY = (cellHeight - blockHeight) / 2;

			// Calculate the final top-left position (x, y) for the *BLOCK*
			int blockX = cellStartX + offsetX;
			int blockY = cellStartY + offsetY;

			Block tempBlock(blockX, blockY, blockWidth, blockHeight, i + j);
			blocks.push_back(tempBlock);

			std::cout << "Block " << i * columns + j << " at (" << blockX << ", " << blockY << ")\n";
		}
	}
}

void BlockHandler::render(SDL_Renderer* renderer) {
	for (auto& block : blocks) {
		block.render(renderer);
	}
	removeBlocks();
}

void BlockHandler::removeBlocks() {
	for (auto it = blocks.begin(); it != blocks.end(); ) {
		if (it->isDestroyed()) {
			it = blocks.erase(it); // Remove block and get the next iterator
			std::cout << "Block Erased" << std::endl;
		}
		else {
			++it; // Move to the next block if not removed
		}
	}
}

std::vector<Block>& BlockHandler::getBlocks() {
	return blocks;
}