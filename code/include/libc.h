#ifndef LIBC_H
#define LIBC_H

// C library routines from the SDK's libc, so they keep C linkage.
extern "C" {
char *strncpy(char *destination, const char *source, unsigned int count);
int memcmp(const void *first, const void *second, unsigned int count);
void *memset(void *destination, int value, unsigned int count);
char *strcpy(char *destination, const char *source);
char *strstr(const char *string, const char *search);
int sprintf(char *buffer, const char *format, ...);
void srand(unsigned int seed);
}

#endif
