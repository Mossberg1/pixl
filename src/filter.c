#include "filter.h"

enum RGBColor {
    RED = 0,
    GREEN = 1,
    BLUE = 2
};

void grayscale(unsigned char* data, int width, int height, int channels) {
    size_t size = width * height * channels;
    for (unsigned char* pixel = data; pixel < (size + data); pixel += channels) {
        unsigned char gray = (pixel[RED] + pixel[GREEN] + pixel[BLUE]) / 3;
        pixel[RED] = pixel[GREEN] = pixel[BLUE] = gray;
    }
}