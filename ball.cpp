#include "ball.h"
#include <random>
#include <iostream>


Ball::Ball(int x, int y, int radius, float xVel, float yVel)
	: xVel(xVel), yVel(yVel)
{
	rect.x = x;
	rect.y = y;
	rect.w = radius * 2;
	rect.h = radius * 2;
}

void Ball::update(int screenWidth, int screenHeight, Paddle& paddle, BlockHandler& blockHandler, Player& player) {
	// Send ball flying initially
	rect.x += xVel;
	rect.y += yVel;

	// Handle wall collisions
	if (rect.x < 0) {
		xVel = -xVel;
	}
	if (rect.x + rect.w > screenWidth) {
		xVel = -xVel;
	}
	if (rect.y < 0) {
		yVel = -yVel;
	}
	if (rect.y + rect.h > screenHeight) {
		restart(screenWidth, screenHeight);
		player.decreaseHealth(1);
	}

	// Handle paddle collisions
	SDL_FRect paddleBounds = paddle.getBounds();

	if (SDL_HasRectIntersectionFloat(&rect, &paddleBounds)) {
		std::cout << "Paddle Hit" << std::endl;

		float ballLeft = rect.x;
		float ballRight = rect.x + rect.w;
		float ballTop = rect.y;
		float ballBottom = rect.y + rect.h;

		float paddleLeft = paddleBounds.x;
		float paddleRight = paddleBounds.x + paddleBounds.w;
		float paddleTop = paddleBounds.y;
		float paddleBottom = paddleBounds.y + paddleBounds.h;

		float overlapLeft = ballRight - paddleLeft;
		float overlapRight = paddleRight - ballLeft;
		float overlapTop = ballBottom - paddleTop;
		float overlapBottom = paddleBottom - ballTop;

		float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

		if (minOverlap == overlapLeft) {
			// Left side
			xVel = -std::abs(xVel);
		}
		else if (minOverlap == overlapRight) {
			// Right side
			xVel = std::abs(xVel);
		}
		else if (minOverlap == overlapTop) {
			// Top
			yVel = -std::abs(yVel);
		}
		else if (minOverlap == overlapBottom) {
			// Bottom
			yVel = std::abs(yVel);
		}
	}

	// Handle block collisions
	// !!! FIXME: Remove rect while still having fade out animation to remove edge cases
	auto& blocks = blockHandler.getBlocks();

	for (auto& block : blocks) {
		SDL_FRect blockBounds = block.getBounds();
		if (SDL_HasRectIntersectionFloat(&rect, &blockBounds)) {
			std::cout << "Block hit, health is: " << block.getHealth() << std::endl;
			
			float ballLeft = rect.x;
			float ballRight = rect.x + rect.w;
			float ballTop = rect.y;
			float ballBottom = rect.y + rect.h;

			float blockLeft = blockBounds.x;
			float blockRight = blockBounds.x + blockBounds.w;
			float blockTop = blockBounds.y;
			float blockBottom = blockBounds.y + blockBounds.h;

			float overlapLeft = ballRight - blockLeft;
			float overlapRight = blockRight - ballLeft;
			float overlapTop = ballBottom - blockTop;
			float overlapBottom = blockBottom - ballTop;

			float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

			if (minOverlap == overlapLeft) {
				// Left side
				xVel = -std::abs(xVel);
			}
			else if (minOverlap == overlapRight) {
				// Right side
				xVel = std::abs(xVel);
			}
			else if (minOverlap == overlapTop) {
				// Top
				yVel = -std::abs(yVel);
			}
			else if (minOverlap == overlapBottom) {
				// Bottom
				yVel = std::abs(yVel);
			}

			if (block.getHealth() <= 1) {
				block.explode();
				player.increaseScore(5);
			}
			else {
				block.setHealth(block.getHealth() - 1);
				player.increaseScore(1);
			}

			break;
		}
	}
}

void Ball::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	const int radius = rect.w / 2;
	const int centerX = rect.x + radius;
	const int centerY = rect.y + radius;

	for (int y = -radius; y <= radius; y++) {
		int xSpan = static_cast<int>(sqrt(radius * radius - y * y));
		SDL_RenderLine(renderer, centerX - xSpan, centerY + y, centerX + xSpan, centerY + y);
	}
}

void Ball::restart(int screenWidth, int screenHeight) {
	rect.x = (screenWidth - rect.w) / 2;
	rect.y = (screenHeight - rect.h) / 2;

	// Randomize x so its not the same each time

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, 1);

	if (distribution(generator) == 0) {
		xVel = -xVel;
	}
	else {
		xVel = xVel;
	}
	rect.x += xVel;
	rect.y += yVel;
}

SDL_FRect Ball::getBounds() const {
	return rect;
}