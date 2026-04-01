#ifndef FILTER_H
#define FILTER_H

#include <stddef.h>

#include "image.h"

enum RGBColor {
    RED = 0,
    GREEN = 1,
    BLUE = 2
};

typedef struct {
    const char* name;
    void (*apply)(Image* img);
} Filter;

Filter* get_filter(const char* name);

void grayscale(Image* img);
void sepia(Image* img);

#endif