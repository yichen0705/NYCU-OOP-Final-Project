#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

struct Color {
    Color() = default;
    Color(uint8_t r, uint8_t g, uint8_t b) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 255;
    }

    uint8_t r, g, b, a;
};

#endif
