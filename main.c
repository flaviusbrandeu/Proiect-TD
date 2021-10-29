#include <stdio.h>
#include <stdlib.h>
#include "at_parser/parser.h"

#define MAXBUFLEN 4096

int main(int argc, char *argv[]) {
    char *file_path;
    uint8_t source[MAXBUFLEN + 1];
    uint16_t newLen;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "Error: program expects path to file as argument\n");
        exit(1);
    }

    file_path = argv[1];
    printf("%s\n", file_path);
    if (!(fp = fopen(file_path, "rb"))) {
        perror(file_path);
    }

    newLen = fread(source, sizeof(char), MAXBUFLEN, fp);
    do {
        if (ferror(fp)) {
            perror(file_path);
        } else {
            source[newLen] = '\0'; /* Just to be safe. */
            for (int i = 0; i < newLen; i++) {
                printf("%c", source[i]);
            }
        }
    } while ((newLen = fread(source, sizeof(char), MAXBUFLEN, fp)));
    fclose(fp);
    return 0;
}
