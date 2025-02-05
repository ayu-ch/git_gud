#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "hash_object.h"
#include "cat-file.h"

void parse_args(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "init") == 0) {
        init();
    } else if (strcmp(argv[1], "hash-object") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: %s hash-object <file>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        hash_object(argv[2]);
    } else if (strcmp(argv[1], "cat-file") == 0) { 
        if (argc < 3) {
            fprintf(stderr, "Usage: %s cat-file <hash>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        cat_file(argv[2]);
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);
    return 0;
}
