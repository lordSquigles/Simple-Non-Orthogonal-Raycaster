#include "map.h"
#include "util.h"

Wall::Wall(float startX, float startY, float endX, float endY, float height, uint32_t wallColor) {
	p.x = startX;
	q.x = endX;
	p.y = startY;
	q.y = endY;
	h = height;
	m = (q.y - p.y) / (q.x - p.x);
	color = wallColor;

	// creates components of wall's standard form equation  
	a = q.y - p.y;
	b = p.x - q.x;
	c = a * p.x + b * p.y;
}

Map::Map(uint32_t sky, uint32_t ground, float light, size_t imgWidth, size_t imgHeight) {
	
	// sky and ground colors
	brightness = light;
	skyColor = sky;
	groundColor = ground;

	unpackColor(skyColor, skyR, skyG, skyB, skyA);
	unpackColor(groundColor, groundR, groundG, groundB, groundA);

	// dimensioning
	rectWidth = (imgWidth / 6) / w; // map width is 1/6 that of the screen
    rectHeight = rectWidth;

	mapX = imgWidth - w * rectWidth;
	mapY = imgHeight - h * rectHeight;
}