#ifndef UTILS_H
#define UTILS_H

#include <openssl/sha.h>

int create_dir_if_not_exists(const char *dir);
void hash_file(const char *filename, unsigned char *hash);
void hash_to_string(unsigned char *hash, char *hash_str);

#endif
