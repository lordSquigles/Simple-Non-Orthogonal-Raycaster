#include "player.h"

Player::Player(float spawnX, float spawnY, float spawnZ, float spawnA, float sfov) {
	x = spawnX;
	y = spawnY;
	z = spawnZ;
	a = spawnA;
	fov = sfov;
	vo = 0;
}