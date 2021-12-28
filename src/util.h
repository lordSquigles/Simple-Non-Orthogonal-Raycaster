#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <cstdint>

void unpackColor(const uint32_t& color, uint8_t &r, uint8_t& g, uint8_t &b, uint8_t &a);
uint32_t packColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255);

#endif