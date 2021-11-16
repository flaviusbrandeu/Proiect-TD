//
// Created by flavius on 28.10.2021.
//

#ifndef __AT_COMMAND_PARSER__
#define __AT_COMMAND_PARSER__

#include <stdint.h>

#define AT_COMMAND_MAX_LINES 100
#define AT_COMMAND_MAX_LINE_SIZE 100

// Variables and types declaration

typedef struct{
    // line terminator '\0' => maximum 99 characters
    uint8_t characters[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINE_SIZE];
    uint8_t status; // ok - 1, error - 2
    uint8_t line_count;
} AT_COMMAND_DATA;

extern AT_COMMAND_DATA data;

typedef enum {
    STATE_MACHINE_NOT_READY,
    STATE_MACHINE_READY_OK,
    STATE_MACHINE_READY_ERROR,
} STATE_MACHINE_RETURN_VALUE;

// Functions declaration
STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t current_char);

#endif //__AT_COMMAND_PARSER__
