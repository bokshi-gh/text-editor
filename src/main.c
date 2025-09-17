#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "terminal.h"

int main(void) {
    enableRawMode();
    enableAlternateBuffer();

    printf("Raw mode enabled. Type 'q' to quit.\n");

    char c;
    while (1) {
        int n = read(STDIN_FILENO, &c, 1);

        if (n == -1 && errno != EAGAIN) {
            perror("read");
            exit(1);
        }
        if (n == 0) continue; // timeout, no input

        if (c == 'q') break;

        if (c < 32) {
            printf("%d\n", c);  // control char
        } else {
            printf("%c (%d)\n", c, c);
        }
    }

    return 0;
}

