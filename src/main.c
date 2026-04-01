#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "image.h"
#include "filter.h"

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

    Image img = load_image(infile);
    if (!img.data) {
        return 1;
    }

    if (filter) {
        Filter* f = get_filter(filter);
        if (!f) {
            fprintf(stderr, "Unknown filter: %s\n", filter);
            free_image(&img);
            return 1;
        }

        f->apply(&img);
    }

    if (!outfile) {
        outfile = infile;
        if (!overwrite) {
            printf("No output file specified, overwrite '%s'? [y/N] ", infile);
            char ch = getchar();
            if (ch != 'y' && ch != 'Y') {
                printf("Aborted.\n");
                free_image(&img);
                return 0;
            }
        }
    }

    write_image(outfile, &img);

    free_image(&img);

    return 0;

usage: 
    fprintf(stderr, "Usage: %s <infile> [options]\n", argv[0]);
    return 1;
}
