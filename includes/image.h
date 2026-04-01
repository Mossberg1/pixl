#ifndef IMAGE_H
#define IMAGE_H

typedef enum {
    JPG,
    PNG,
    UNKNOWN
} ImageType;

typedef struct {
    int width;
    int height;
    int channels;
    ImageType type;
    unsigned char* data;
} Image;

Image load_image(char* filepath);
void write_image(char* filepath, Image* img);
void free_image(Image* img);

#endif