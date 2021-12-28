#include "util.h"
#include "map.h"


uint32_t packColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
	return (a << 24) + (b << 16) + (g << 8) + r;
}

void unpackColor(const uint32_t& color, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) {
	r = (color >> 0) & 255;
	g = (color >> 8) & 255;
	b = (color >> 16) & 255;
	a = (color >> 24) & 255;
}
