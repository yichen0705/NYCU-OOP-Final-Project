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

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 255;
};

#endif
