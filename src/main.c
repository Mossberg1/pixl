#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "filter.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        goto usage;
    }

    char* infile = argv[1];

    optind = 2;
    int opt;
    char* outfile = NULL;
    char* filter = NULL;
    bool overwrite = false;

    while ((opt = getopt(argc, argv, "f:o:y")) != -1) {
        switch (opt) {
            case 'f': filter = optarg; break;
            case 'o': outfile = optarg; break;
            case 'y': overwrite = true; break;
            case '?': goto usage;
        }
    }

    int width, height, channels;
    unsigned char* data = stbi_load(infile, &width, &height, &channels, 0);
    if (!data) {
        return 1;
    }

    if (filter) {
        if (strcmp(filter, "grayscale") == 0)
            grayscale(data, width, height, channels);
    }

    if (!outfile) {
        outfile = infile;
        if (!overwrite) {
            printf("No output file specified, overwrite '%s'? [y/N] ", infile);
            char ch = getchar();
            if (ch != 'y' && ch != 'Y') {
                printf("Aborted.\n");
                stbi_image_free(data);
                return 0;
            }
        }
    }

    stbi_write_jpg(outfile, width, height, channels, data, 100);

    stbi_image_free(data);

    return 0;

usage: 
    fprintf(stderr, "Usage: %s <infile> [options]\n", argv[0]);
    return 1;
}
