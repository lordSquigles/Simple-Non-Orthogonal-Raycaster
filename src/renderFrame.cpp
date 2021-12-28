#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <iostream>
#include "renderFrame.h"
#include "util.h"

void drawScene(Map &map, Display &frame, Player &player) { 

	for (int i = 0; i < frame.w; i++) {

		float height = 0.f;

		float f = player.a - player.fov + player.fov * 2 * i / frame.w;

		Point rayEnd;

		rayEnd.x = player.x + cos(f) * map.drawDistance; // create endpoints of ray
		rayEnd.y = player.y + sin(f) * map.drawDistance;

		float a = rayEnd.y - player.y; // create standard form of segment
		float b = player.x - rayEnd.x;
		float c = a * (player.x) + b * (player.y);

		float drawDist = sqrt(pow(rayEnd.x - player.x, 2) + pow(rayEnd.y - player.y, 2));

		float dist = drawDist;
		uint32_t wallColor = 0;
		float rayX = rayEnd.x, rayY = rayEnd.y;

		for (int i = 0; i < map.walls.size(); i++) {
			Wall &wall = map.walls[i];

			float den = (a * wall.b) - (wall.a * b); // denominator value is the same for x and y, so no need to calculate it again

			float x = ((wall.b * c) - (b * wall.c)) / den; // finds the x-value of where the lines intersect
			float y = ((a * wall.c) - (wall.a * c)) / den;

			if (isnan(x) || isnan(y)) { // point is unreal
				x = rayEnd.x;
				y = rayEnd.y;
				continue;
			}

			if (x < std::min(wall.p.x, wall.q.x) || x > std::max(wall.p.x, wall.q.x) || y < std::min(wall.p.y, wall.q.y) || y > std::max (wall.p.y, wall.q.y)) { // point is outside the wall's bounds
				x = rayEnd.x;
				y = rayEnd.y;
				continue; 
			}

			if ((rayEnd.x - player.x > 0 && x - player.x < 0) || (rayEnd.x - player.x < 0 && x - player.x > 0) || (rayEnd.y - player.y > 0 && y - player.y < 0) || (rayEnd.y - player.y < 0 && y - player.y > 0)) { // line is behind the player's view
				x = rayEnd.x;
				y = rayEnd.y;
				continue;
			}

			float newDist = sqrt(pow(x - player.x, 2) + pow(y - player.y, 2));

			if (newDist >= dist) { // skips if ray is farther than draw distance or closest recorded hit
				continue;
			}

			height = wall.h;
			rayX = x; rayY = y;
			dist = newDist; 
			wallColor = wall.color;
		}
		
		// render 3d view

		int horizon = frame.h / 2 + player.vo;
		int initialH = frame.h / (dist * cos(f - player.a)); // correction cos fixes "fisheye" effect
		int columnH = height * initialH; // creates the height of each column inversely proportional to the distance between the player and the point at which the ray stopped
		int wallTop = horizon - ((columnH + columnH - initialH) / 2); // midline of screen minus half of the column height 
		int wallBottom = wallTop + columnH;

		for (int j = 0; j < frame.h; j++) { // not branchless, but g++ will optimize this better than the other options
			if (j < wallTop) {
				frame.drawPixel(i, j, map.skyColor); 
			}
			else if (j >= wallBottom) {
				float shade = std::fmax(0, 1 - (map.brightness / 12) / float(j - horizon));
                frame.drawPixel(i, j, packColor(map.groundR * shade, map.groundG * shade, map.groundB * shade));
			}
			else {
				uint8_t r, g, b, a;
				unpackColor(wallColor, r, g, b, a);

				float shade = std::fmin(1, map.brightness / (dist * dist));
				frame.drawPixel(i, j, packColor(r * shade, g * shade, b * shade));
			}
		}
	}
	return;
}
