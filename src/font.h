#ifndef FONT_H
#define FONT_H

struct Font {
    size_t width, height, count, sheetWidth;
    std::vector<uint32_t> fontSheet;

    Font(const std::string file, const size_t letterWidth);
    std::string fileName;
};

#endif 