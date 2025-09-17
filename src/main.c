#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "../include/terminal.h"
#include "../include/editor.h"
#include "../include/keypress.h"

int main(void) {
    enableRawMode();
    enableAlternateBuffer();

    Editor editor = initEditor();

    // printf("Raw mode enabled. Type 'q' to quit.\n");

    char c;
    while (1) {
	clearTerminal();
	
	renderBuffer(&editor);
	moveCursor(HOME);
	char cursor[100];
	sprintf(cursor, "\x1b[%d;%dH", editor.row, editor.column);
	write(STDOUT_FILENO, cursor, 6);

        int n = read(STDIN_FILENO, &c, 1);

        if (n == -1 && errno != EAGAIN) {
            perror("read");
	    disableAlternateBuffer();
	    exit(1);
        }
        if (n == 0) continue; // timeout, no input
	
	handleKeyPress(&editor, c);
        }

    disableAlternateBuffer();
    return 0;
}

