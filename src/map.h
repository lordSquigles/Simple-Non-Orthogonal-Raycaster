#pragma once

#ifndef MAP_H
#define MAP_H

#include <vector>

struct Point {
	double x, y;
};

struct Wall {
	Point p, q;
	float a, b, c;
	float m, h;
	uint32_t color;

	Wall(float startX, float startY, float endX, float endY, float height, uint32_t wallColor);
};

struct Map {

	bool shown = 0;

	int rectWidth;
	int rectHeight;
	int drawDistance = 80;
	float brightness;

	uint32_t skyColor;
	uint32_t groundColor;

	uint8_t groundR, groundG, groundB, groundA;
    uint8_t skyR, skyG, skyB, skyA;

	std::vector<Wall> walls;
	int w = 32, h = 32;
	int mapX, mapY;

	Map(uint32_t sky, uint32_t ground, float light, size_t imgWidth, size_t imgHeight);
};

#endif

