#include <string.h>

#include "filter.h"

void grayscale(Image* img);
void sepia(Image* img);
static unsigned char clamp(int value);

static const Filter filters[] = {
    { "grayscale", grayscale },
    { "sepia", sepia },
    { NULL, NULL }
};

Filter* get_filter(const char* name) {
    for (int i = 0; filters[i].name != NULL; i++) {
        if (strcmp(name, filters[i].name) == 0) {
            return (Filter*)&filters[i];
        }
    }

    return NULL;
}

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

        pixel[RED]   = clamp(red);
        pixel[GREEN] = clamp(green);
        pixel[BLUE]  = clamp(blue);
    }
}

static unsigned char clamp(int value) {
    return value > 255 ? 255 : (value < 0 ? 0 : value);
}