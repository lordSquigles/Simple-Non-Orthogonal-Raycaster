#define _USE_MATH_DEFINES
#define SDL_MAIN_HANDLED
#include "SDL2-2.0.18\include\SDL.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>

#include "util.h"
#include "gameState.h"
#include "player.h"
#include "display.h"
#include "renderFrame.h"
#include "map.h"
#include "font.h"

int main() {
	
	// Initialize

    size_t imgWidth = 1024;
    size_t imgHeight = 768;

	Display frame{imgWidth, imgHeight, std::vector<uint32_t>(imgWidth * imgHeight, packColor(0, 0, 0))};

    Map map(packColor(21, 228, 239), packColor(32, 226, 18), 72, imgWidth, imgHeight);
    Font courier("Textures/fonts/courier.png", 27); // initialize font object with font sheet

    // SDL

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)) {
        printf("Failed to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    // Create SDL window
    if (SDL_CreateWindowAndRenderer(frame.w, frame.h, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)) {
        printf("Failed to create SDL window and renderer: %s", SDL_GetError());
    }

    // write framebuffer to an SDL texture
    SDL_Texture* frameTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, frame.w, frame.h);
    if (!frameTexture) {
        printf("Failed to create framebuffer texture: %s", SDL_GetError());
    }

    SDL_Event event;

    // todo: replace hardcoded map details with the reading of a map file

    map.walls.push_back(Wall{8.f, 8.f, 14.f, 10.f, 1.1f, packColor(255, 0, 0) });
    map.walls.push_back(Wall{ 8.f, 15.f, 18.f, 19.f, 1.4f, packColor(0, 255, 0) });
    map.walls.push_back(Wall{ 8.f, 8.f, 8.f, 15.f, 2.f, packColor(0, 0, 255) });
    map.walls.push_back(Wall{ 14.f, 10.f, 18.f, 19.f, 1.f, packColor(255, 255, 0) });

    map.walls.push_back(Wall{ 18.f, 24.f, 26.f, 21.f, 1.3f, packColor(0, 255, 255) });
    map.walls.push_back(Wall{ 2.f, 2.f, 1.f, 8.f, 1.f, packColor(255, 0, 255) });

    GameState gs{frame, map, Player(4.f, 4.f, 0.f, M_PI / 2.f, imgWidth * (M_PI / 6.f) / 1024), courier, window, renderer, frameTexture, 0};

    uint32_t lastTime = 0;
    uint8_t fps;
    std::vector<uint8_t> fpsLog;
    uint8_t avgFps;

	while (1) { // main game loop

        float dt = (SDL_GetTicks() - lastTime) / 1000.0;
        lastTime = SDL_GetTicks();
		
        if (dt <= 0) dt = 1; //prevent division by zero
      
        fps = 1 / dt;

        fpsLog.push_back(fps);
        /*if (fpsLog.size() > 20) { // comment for avg fps of entire run
            fpsLog.erase(fpsLog.begin()); // delete the first element
        }*/

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) break;

        avgFps = std::accumulate(fpsLog.begin(), fpsLog.end(), 0) / fpsLog.size();
		gs.update(event, fps);
	}

    printf("%i", avgFps);
    SDL_DestroyTexture(frameTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

	return 0;
}
