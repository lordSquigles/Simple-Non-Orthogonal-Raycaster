#pragma once

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "gameState.h"
#include "player.h"
#include "display.h"
#include "renderFrame.h"
#include "map.h"
#include "SDL2-2.0.18\include\SDL.h"

struct GameState {

	Display frame;
	Map map;
	Player player;
	Font console;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* frameTexture;

	bool paused = 0;
	size_t mapX, mapY;

	void update(SDL_Event& event, int fps);

	private: 
		void handleInput(SDL_Event& event);
};

#endif
