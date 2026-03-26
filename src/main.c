#include "filter.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
    const char* infile = "images/in-test.jpg";
    const char* outfile = "images/out-test.jpg";

    int width, height, channels;
    unsigned char* data = stbi_load(infile, &width, &height, &channels, 0);
    if (!data) {
        return -1;
    }

    grayscale(data, width, height, channels);

    printf("width: %d, height: %d, channels: %d\n", width, height, channels);

    stbi_write_jpg(outfile, width, height, channels, data, 100);

    stbi_image_free(data);

    return 0;
}