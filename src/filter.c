#include "filter.h"

enum RGBColor {
    RED = 0,
    GREEN = 1,
    BLUE = 2
};

void grayscale(Image* img) {
    size_t size = img->width * img->height * img->channels;
    for (unsigned char* pixel = img->data; pixel < (size + img->data); pixel += img->channels) {
        unsigned char gray = (pixel[RED] + pixel[GREEN] + pixel[BLUE]) / 3;
        pixel[RED] = pixel[GREEN] = pixel[BLUE] = gray;
    }
}