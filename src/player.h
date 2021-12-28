#pragma once

#ifndef PLAYER_H
#define PLAYER_H

struct Player {
	Player(float spawnX, float spawnY, float spawnZ, float spawnA, float sfov);
	float x, y, z, a, fov, fovMultiplier = 1;
	float speedMultiplier, turnMultiplier, da = 0, vo = 0;
	int health, weapon, speed = 16;
};

#endif