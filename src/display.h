#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>
#include <vector>

#include "map.h"
#include "player.h"
#include "font.h"

struct Display {
	size_t w, h; // dimensions
	std::vector<uint32_t> imgBuffer; // frameBuffer array

	void clear(const uint32_t color);
	void drawPixel(const size_t x, const size_t y, const uint32_t color);
	void drawLine(const float startX, const float startY, const float endX, const float endY, const uint32_t color);
	void drawRectangle(const size_t x, const size_t y, const size_t w, const size_t h, const uint32_t color);
	void drawMap(size_t x, size_t y, Map& map, Player& player);
	void type(const size_t x, const size_t y, const Font &font, const uint32_t textColor, const std::string text);
};

#endif
