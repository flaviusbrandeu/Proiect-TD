#include <stdio.h>
#include "at_parser/parser.h"

int main() {
    switch(at_command_parse(' ')){
        case STATE_MACHINE_READY_OK:
            printf("STATE_MACHINE_READY_OK");
            break;
        case STATE_MACHINE_READY_ERROR:
            printf("STATE_MACHINE_READY_ERROR");
            break;
        case STATE_MACHINE_NOT_READY:
            printf("STATE_MACHINE_NOT_READY");
            break;
    }
    return 0;
}
