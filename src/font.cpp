#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>
#include "stb_image.h"

#include "util.h"
#include "font.h"

Font::Font(const std::string file, const size_t charWidth) : sheetWidth(0), height(0), count(0), width(0), fontSheet() {
    int nchannels = -1, w, h;
    unsigned char* pixmap = stbi_load(file.c_str(), &w, &h, &nchannels, 0); // load image of passed filename into memory by the "pixmap" pointer
    if (!pixmap) {
        std::cerr << "Error: can not load the textures" << std::endl;
        return;
    }

    if (4 != nchannels) {
        std::cerr << "Error: the texture must be a 32 bit image" << std::endl;
        stbi_image_free(pixmap);
        return;
    }
    
    fileName = file;
    count = w / charWidth; // number of textures in a texture file
    width = charWidth; // width of one texture
    sheetWidth = w; // width of the passed image
    height = h; // height of the passed image

    fontSheet = std::vector<uint32_t>(w * h); // creates an array, fontSheet, the size of the passed image array (width * height)

    for (int i = 0; i < w; i++) { // packs a 32-bit color from each of the loaded image's elements (pixels) and writes it to the corresponding elements of the img array
        for (int j = 0; j < h; j++) {
            uint8_t r = pixmap[(i + j * w) * 4 + 0];
            uint8_t g = pixmap[(i + j * w) * 4 + 1];
            uint8_t b = pixmap[(i + j * w) * 4 + 2];
            uint8_t a = pixmap[(i + j * w) * 4 + 3];
            fontSheet[i + j * w] = packColor(r, g, b, a); // sets each incremented element of the img[] array to contain the 32-bit color value that exists in the texture
        }
    }
    stbi_image_free(pixmap);
}
