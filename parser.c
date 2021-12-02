//
// Created by flavius on 28.10.2021.
//

#include "parser.h"


STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t current_char, COMMAND_TYPE command_type) {
    static uint8_t state = 0;
    static uint8_t col_index = 0;

//    printf("state %d\n", state);
    switch (state) {
        case 0: {
            if (current_char == '\r') {
                state = 1;
                data.line_count = 0;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_NOT_READY;
            }
        }
        case 1: {
            if (current_char == '\n') {
                if (command_type == SPECIAL_COMMAND) {
                    state = 11;
                } else {
                    state = 2;
                }
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 2: {
            if (current_char == 'O') {
                state = 3;
                return STATE_MACHINE_NOT_READY;
            } else if (current_char == 'E') {
                state = 7;
                return STATE_MACHINE_NOT_READY;
            } else if (current_char == '+') {
                state = 11;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 3: {
            if (current_char == 'K') {
                state = 4;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 4: {
            if (current_char == '\r') {
                state = 5;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 5: {
            if (current_char == '\n') {
                state = 0;
//                data.line_count = 0;
//                for (uint8_t i = 0; i < data.line_count; i++) {
//                    for (uint8_t j = 0; j < strlen(data.characters[i]); j++) {
//                        printf("%c", data.characters[i][j]);
//                    }
//                    printf("\n");
//                }
                return STATE_MACHINE_READY_OK;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 7: {
            if (current_char == 'R') {
                state = 8;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 8: {
            if (current_char == 'R') {
                state = 9;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 9: {
            if (current_char == 'O') {
                state = 10;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 10: {
            if (current_char == 'R') {
                state = 4;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 11: {
            if (current_char >= 32 && current_char <= 126) {
                state = 11;
                if (data.line_count < AT_COMMAND_MAX_LINES) {
                    if (col_index < AT_COMMAND_MAX_LINE_SIZE - 1) {
                        data.characters[data.line_count][col_index] = current_char;
                        col_index++;
                    }
                }
                return STATE_MACHINE_NOT_READY;
            } else if (current_char == '\r') {
                state = 12;
                if (data.line_count < AT_COMMAND_MAX_LINES) {
                    data.characters[data.line_count][col_index] = '\0';
                    col_index = 0;
                    data.line_count++;
                }
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 12: {
            if (current_char == '\n') {
                state = 13;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 13: {
            if (current_char == '+') {
                if (command_type == USUAL_COMMAND) {
                    state = 11;
                    return STATE_MACHINE_NOT_READY;
                } else {
                    return STATE_MACHINE_READY_ERROR;
                }
            } else if (current_char == '\r') {
                state = 14;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 14: {
            if (current_char == '\n') {
                state = 15;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
        case 15: {
            if (current_char == 'E') {
                state = 7;
                return STATE_MACHINE_NOT_READY;
            } else if (current_char == 'O') {
                state = 3;
                return STATE_MACHINE_NOT_READY;
            } else {
                return STATE_MACHINE_READY_ERROR;
            }
        }
    }
}
