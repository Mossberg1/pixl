#include <stdlib.h>
#include <string.h>

#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

static ImageType get_image_type(const char* filepath);

Image load_image(char* filepath) {
    Image img;

    img.type = get_image_type(filepath);
    img.data = stbi_load(filepath, &img.width, &img.height, &img.channels, 0);

    return img;
}

void write_image(char* filepath, Image* img) {
    switch (img->type) {
        case JPG: 
            stbi_write_jpg(filepath, img->width, img->height, img->channels, img->data, 100);
            break;
        case PNG:
            stbi_write_png(filepath, img->width, img->height, img->channels, img->data, img->width * img->channels);
            break;
        default:
            break;
    }
}

void free_image(Image* img) {
    stbi_image_free(img->data);
}

static ImageType get_image_type(const char* filepath) {
    char* ext = strrchr(filepath, '.');
    if (!ext) {
        return UNKNOWN;
    }

    ext++;

    if (strcasecmp(ext, "jpg") == 0 || strcasecmp(ext, "jpeg") == 0) {
        return JPG;
    }
    else if (strcasecmp(ext, "png") == 0) {
        return PNG;
    }

    return UNKNOWN;
}