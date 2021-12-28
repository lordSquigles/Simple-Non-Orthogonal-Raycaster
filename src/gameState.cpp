#include <vector>
#include <cassert>
#include <iostream>

#include "gameState.h"
#include "util.h"
#include "renderFrame.h"

float deg = M_PI / 180;
float dx = 0, dy = 0;
int turn = 0;
int look = 0;
int forwards = 0;
int sideways = 0;

float movSpeed = 1;

bool pause = 0;
bool stats = 0;

void GameState::update(SDL_Event& event, int fps) {

	handleInput(event);

	frame.clear(packColor(0, 0, 0)); // clear display between frames

	if (pause == 0) {
		movSpeed = (150.f / fps); // set movement speed to be constant regardless of framerate
		drawScene(map, frame, player);

		if (map.shown == 1) { // draw map
			frame.drawMap(map.mapX, map.mapY, map, player);
		}

		if (stats == 1) {
			frame.type(0, 0, console, packColor(0, 0, 0), "FPS: " + std::to_string(fps));
			frame.type(243, 0, console, packColor(0, 0, 0), "movSpeed: " + std::to_string(movSpeed));
		}
	}

	SDL_UpdateTexture(frameTexture, NULL, reinterpret_cast<void*>(frame.imgBuffer.data()), frame.w * 4);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, frameTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void GameState::handleInput(SDL_Event& event) {
	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) turn = 0;
		else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN) look = 0;
        else if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s) forwards = 0, dx = 0, dy = 0; 
		else if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d) sideways = 0, dx = 0, dy = 0;
	}
	if (SDL_KEYDOWN == event.type) {
		if (pause == 0) {
			switch (event.key.keysym.sym) {
				case SDLK_RIGHT: turn = 1; break;
				case SDLK_LEFT: turn = -1; break;
				case SDLK_UP: look = 1; break;
				case SDLK_DOWN: look = -1; break;
				case SDLK_w: forwards = 1; break;
				case SDLK_s: forwards = -1; break;
				case SDLK_a: sideways = 1; break;
				case SDLK_d: sideways = -1; break;
				case SDLK_m: map.shown = (map.shown == 0) ? 1 : 0; break; // toggle map
				case SDLK_p: pause = 1; break; // "p" key toggles the pause bool
				case SDLK_BACKQUOTE: consoleOpen = 1; break;
				case SDLK_SLASH: stats = (stats == 0) ? 1 : 0; break; // toggle stats
				default: break;
			}
		}
		else {
			switch (event.key.keysym.sym) {
				case SDLK_p: pause = 0; break; // "p" key toggles the pause bool
				default: break;
			}
		}
	}

	player.a += turn * deg * movSpeed; // player angle
	player.vo += look * 4 * movSpeed; // player vertical offset (used for y-shearing vertical look)

	dx = forwards * cos(player.a) / player.speed + sideways * cos(player.a - M_PI / 2) / player.speed; // forwards/backwards and sideways motion
	dy = forwards * sin(player.a) / player.speed + sideways * sin(player.a - M_PI / 2) / player.speed;

	/*for (int i = 0; i < map.walls.size(); i ++) {
		
	}*/
	player.x += dx * movSpeed; // accounts for different cpu speeds
	player.y += dy * movSpeed;
}



