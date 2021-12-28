#define _USE_MATH_DEFINES
#include <cassert>
#include <cmath>
#include <iostream>
#include "display.h"
#include "util.h"
#include "font.h"

void Display::clear(const uint32_t color) {
	imgBuffer = std::vector<uint32_t>(w * h, color);
}

void Display::drawPixel(const size_t x, const size_t y, const uint32_t color) {
	assert(imgBuffer.size() == w * h);
    if (!(x < w) || !(x > 0) || !(y < h) || !(y > 0)) return;
	imgBuffer[x + y * w] = color;
}

void Display::drawLine(const float start_x, const float start_y, const float end_x, const float end_y, const uint32_t color) {
    float j = start_y;
    int dx = (end_x - start_x);
    int dy = (end_y - start_y);
    if (dx > 0) {
        for (float i = 0; i < dx; i += 0.001 * dx) {
            j += 0.001 * dy;
            if (start_x + i < w && start_x + i > 0 && j < h && j > 0) {
                drawPixel(start_x + i, j, color);
            }
        }
    }
    else if (dx == 0 && dy > 0) {
        for (float i = 0; i < dy; i += 0.001 * dy) {
            if (start_y + i > 0 && start_y + i < h && start_x < w && start_x > 0) {
                drawPixel(start_x, start_y + i, color);
            }
        }
    }
    else if (dx == 0 && dy < 0) {
        for (float i = 0; i > dy; i += 0.001 * dy) {
            if (start_y + i > 0 && start_y + i < h && start_x < w && start_x > 0) {
                drawPixel(start_x, start_y + i, color);
            }
        }
    }
    else {
        for (float i = 0; i > dx; i += 0.001 * dx) {
            j += 0.001 * dy;
            if (start_x + i < w && start_x + i > 0 && j < h && j > 0) {
                drawPixel(start_x + i, j, color);
            }
        }
    }
}

void Display::drawRectangle(const size_t rect_x, const size_t rect_y, const size_t rect_w, const size_t rect_h, const uint32_t color) {
    assert(imgBuffer.size() == w * h);
    for (size_t i = 0; i < rect_w; i++) {
        for (size_t j = 0; j < rect_h; j++) {
            size_t cx = rect_x + i;
            size_t cy = rect_y + j;
            if (cx < w && cy < h) // no need to check for negative values (unsigned variables)
                drawPixel(cx, cy, color);
        }
    }
}

void Display::drawMap(size_t x, size_t y, Map& map, Player& player) {

	for (size_t i = 0; i <= map.w; i++) { // draw x-lines
		drawLine(x + i * map.rectWidth, y, x + i * map.rectHeight, y + map.h * map.rectHeight, packColor(100, 100, 100));
	}

	for (size_t j = 0; j < map.h; j++) { // draw y-lines
		drawLine(x, y + j * map.rectHeight, x + map.w * map.rectWidth, y + j * map.rectHeight, packColor(100, 100, 100));
	}

	drawRectangle(std::max((int)x, std::min(int(x + map.w * map.rectWidth), int(x + player.x * map.rectWidth - 2))), std::max((int)y, std::min(int(y + map.h * map.rectHeight), int(y + player.y * map.rectHeight - 2))), 4, 4, packColor(255, 255, 0)); // draw player
    drawLine(x + player.x * map.rectWidth, y + player.y * map.rectHeight, x + (player.x + 2 * cos(player.a)) * map.rectWidth, y + (player.y + 2 * sin(player.a)) * map.rectHeight, packColor(255, 255, 255));

	for (size_t i = 0; i < map.walls.size(); i++) { // draw walls on map
        Wall &wall = map.walls[i];
		drawLine(x + wall.p.x * map.rectWidth, y + wall.p.y * map.rectHeight, x + wall.q.x * map.rectWidth, y + wall.q.y * map.rectHeight, wall.color);
	}
}

void Display::type(const size_t x, const size_t y, const Font &font, const uint32_t textColor, const std::string text) {
    std::string alphabet = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz?!@#$%^&*()[]{}<>;:'\",./\\-+=`~_| ";
    for (size_t k = 0; k < text.size(); k++) {
        int letterID = alphabet.find(text[k]); // get letterID for each letter passed
        for (size_t i = 0; i < font.width; i ++) {
            for (size_t j = 0; j < font.height; j++) {
                uint8_t r, g, b, a;
                unpackColor(font.fontSheet[i + letterID * font.width + j * font.sheetWidth], r, g, b, a);
                if (a > 128) { // only set non-transparent pixels
                    // modify color of text // scale buffer for different font sizes
                    drawPixel(x + i + k * font.width, y + j, textColor);
                }
            }
        }
    }
}