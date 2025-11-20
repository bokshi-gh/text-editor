#include "../include/terminal.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    enter_alternate_screen_buffer();
    enableRawMode();

    char c = 0;
    while (1) {
        if (read(STDIN_FILENO, &c, 1) == -1) break;

        if (c == 'q') {
            disableRawMode();
            leave_alternate_screen_buffer();
            return EXIT_SUCCESS;
        }

        write(STDOUT_FILENO, &c, 1);
    }

    disableRawMode();
    leave_alternate_screen_buffer();
    return EXIT_SUCCESS;
}

