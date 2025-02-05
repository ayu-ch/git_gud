#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "cat-file.h"

#define OBJECTS_DIR ".git_gud/objects"

void cat_file(const char *oid) {
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", OBJECTS_DIR, oid);

    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}
