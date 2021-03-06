#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define MAXBUFLEN 4096

AT_COMMAND_DATA data;

const COMMAND_TYPE commands_types[] = {USUAL_COMMAND, USUAL_COMMAND, USUAL_COMMAND, SPECIAL_COMMAND, SPECIAL_COMMAND,
                                       USUAL_COMMAND, SMS_COMMAND, USUAL_COMMAND, USUAL_COMMAND, USUAL_COMMAND,
                                       USUAL_COMMAND, USUAL_COMMAND, SPECIAL_COMMAND, USUAL_COMMAND, SPECIAL_COMMAND,
                                       USUAL_COMMAND, SMS_COMMAND, USUAL_COMMAND, SPECIAL_COMMAND, USUAL_COMMAND};

int main(int argc, char *argv[]) {
    char *file_path;
    uint8_t source[MAXBUFLEN + 1];
    uint8_t no_of_commands = 0;
    uint16_t newLen;
    FILE *fp;
    STATE_MACHINE_RETURN_VALUE state = STATE_MACHINE_NOT_READY;

    if (argc != 2) {
        fprintf(stderr, "Error: program expects path to file as argument\n");
        exit(1);
    }

    file_path = argv[1];
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
                state = at_command_parse(source[i], commands_types[no_of_commands]);
                if (state == STATE_MACHINE_READY_OK) {
                    no_of_commands++;
                    printf("STATE_MACHINE_READY_OK\n");
                    for (uint8_t i = 0; i < data.line_count; i++) {
                        for (uint8_t j = 0; j < strlen(data.characters[i]); j++) {
                            printf("%c", data.characters[i][j]);
                        }
                        printf("\n");
                    }
                    printf("\n");
                } else if (state == STATE_MACHINE_READY_ERROR) {
                    break;
                }
            }
        }
    } while ((newLen = fread(source, sizeof(char), MAXBUFLEN, fp)));
    fclose(fp);

    switch (state) {
        case STATE_MACHINE_READY_ERROR:
            printf("STATE_MACHINE_READY_ERROR\n");
            break;
        case STATE_MACHINE_NOT_READY:
            printf("STATE_MACHINE_NOT_READY\n");
            break;
    }

    return 0;
}
