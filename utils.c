#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sys/stat.h>
#include <errno.h>

int create_dir_if_not_exists(const char *dir) {
    char temp[1024];
    snprintf(temp, sizeof(temp), "%s", dir);

    for (char *p = temp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(temp, 0755) == -1 && errno != EEXIST) {
                return -1; 
            }
            *p = '/';
        }
    }

    return mkdir(temp, 0755) == -1 && errno != EEXIST ? -1 : 0;
}

void hash_file(const char *filename, unsigned char *hash) {
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
        exit(EXIT_FAILURE);
    }
    
    fread(buffer, 1, size, file);
    fclose(file);
    
    SHA1(buffer, size, hash);
    free(buffer);
}

void hash_to_string(unsigned char *hash, char *hash_str) {
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(hash_str + (i * 2), "%02x", hash[i]);
    }
    hash_str[SHA_DIGEST_LENGTH * 2] = '\0';
}
