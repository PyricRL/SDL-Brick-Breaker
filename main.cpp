#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <sstream>

#include "paddle.h"
#include "ball.h"
#include "block.h"
#include "player.h"

#include <direct.h>

static SDL_Window* window;
static SDL_Renderer* renderer;

static std::string null = "";
static std::string centered = "center";

bool paused = false;

void renderUI(const std::string& text, TTF_Font* font, int x, int y, const std::string& flags) {
	SDL_Color color = { 255, 255, 255, 255 };

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
	
	if (!surface) {
		SDL_Log("TTF_RenderText_Solid Error: %s", SDL_GetError());
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_Log("SDL_CreateTextureFromSurface Error: %s", SDL_GetError());
		return;
	}

	SDL_FRect dst;

	if (flags == "center") {
		dst = { (float)(x - (surface->w/2)), (float)(y - (surface->h / 2)), (float)surface->w, (float)surface->h};
	}
	else {
		dst = { (float)x, (float)y, (float)surface->w, (float)surface->h };
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderTexture(renderer, texture, nullptr, &dst);

	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);
}

void update(Paddle& paddle, Ball& ball, BlockHandler& blockHandler, Player& player, TTF_Font* font, SDL_Renderer* renderer) {
	paddle.handleInput();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	blockHandler.render(renderer);
	ball.render(renderer);
	paddle.render(renderer);

	std::string liveStr = "Lives: " + std::to_string(player.getHealth());
	std::string scoreStr = "Score: " + std::to_string(player.getScore());

	renderUI(liveStr, font, 0, 0, null);
	renderUI(scoreStr, font, 0, 20, null);
	SDL_RenderPresent(renderer);

	ball.update(800, 600, paddle, blockHandler, player);
	paddle.update(800);
}

void gameOver(Player& player, TTF_Font* bigFont, TTF_Font* smallFont, SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	renderUI("Game Over!", bigFont, 400, 300, centered);

	std::string scoreStr = "Score: " + std::to_string(player.getScore());

	renderUI(scoreStr, smallFont, 400, 340, centered);

	SDL_RenderPresent(renderer);
		
	SDL_Delay(5000);
}

int main(int argc, char* argv[]) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		return 1;
	}

	if (!SDL_CreateWindowAndRenderer("Hello SDL!", 800, 600, 0, &window, &renderer)) {
		SDL_Log("SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
		return 1;
	}

	if (!TTF_Init()) {
		SDL_Log("TTF_Init Error: %s", SDL_GetError());
		return 1;
	}

	TTF_Font* smallFont = TTF_OpenFont("D:/Programming/Projects/C++/SDL Brick Breaker/Assets/Roboto-Regular.ttf", 24);
	TTF_Font* bigFont = TTF_OpenFont("D:/Programming/Projects/C++/SDL Brick Breaker/Assets/Roboto-Regular.ttf", 40);

	if (!smallFont || !bigFont) {
		SDL_Log("Font Initialize Error: %s", SDL_GetError());
		return 1;
	}

	Paddle paddle(350, 550, 100, 20, 0.25);
	Ball ball(10, 10, 10, 0.1, 0.1);
	BlockHandler blockHandler;
	Player player;

	blockHandler.generateBlocks(5, 5, 100, 20, 800, 600);

	ball.restart(800, 600);
	
	bool running = true;

	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		update(paddle, ball, blockHandler, player, smallFont, renderer);

		if (player.getHealth() <= 0) {
			gameOver(player, bigFont, smallFont, renderer);
			running = false;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	TTF_CloseFont(smallFont);
	TTF_CloseFont(bigFont);
	TTF_Quit();

	return 0;
}