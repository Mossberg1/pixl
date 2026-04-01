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

void sepia(Image* img) {
    size_t size = img->width * img->height * img->channels;
    for (unsigned char* pixel = img->data; pixel < (size + img->data); pixel += img->channels) {
        int red   = (pixel[RED] * .393) + (pixel[GREEN] * .769) + (pixel[BLUE] * .189);
        int green = (pixel[RED] * .349) + (pixel[GREEN] * .686) + (pixel[BLUE] * .168);
        int blue  = (pixel[RED] * .272) + (pixel[GREEN] * .534) + (pixel[BLUE] * .131);

        pixel[RED]   = red > 255 ? 255 : red;
        pixel[GREEN] = green > 255 ? 255: green;
        pixel[BLUE]  = blue > 255 ? 255: blue;
    }
}