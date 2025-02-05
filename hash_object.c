#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "hash_object.h"
#include "utils.h" 

#define OBJECTS_DIR ".git_gud/objects"

void hash_object(const char *filename) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    
    hash_file(filename, hash);

    char hash_str[SHA_DIGEST_LENGTH * 2 + 1];
    hash_to_string(hash, hash_str);

    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", OBJECTS_DIR, hash_str);

    if (create_dir_if_not_exists(OBJECTS_DIR) == -1) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(path, "wb");
    if (!out) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    unsigned char *buffer = malloc(size);
    if (!buffer) {
        perror("malloc");
        fclose(file);
        fclose(out);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, size, file);
    fclose(file);

    fwrite(buffer, 1, size, out);
    fclose(out);

    free(buffer);

    printf("%s\n", hash_str);
}
