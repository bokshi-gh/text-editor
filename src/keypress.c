#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/keypress.h"
#include "../include/editor.h"
#include "../include/terminal.h"

void handleKeyPress(Editor *editor){
	char c;
        int n = read(STDIN_FILENO, &c, 1);

        if (n == -1 && errno != EAGAIN) {
            perror("read");
	    disableAlternateBuffer();
	    exit(1);
        }
        if (n == 0) return; // timeout, no input
	if (c == 'q') {
		disableAlternateBuffer();
		exit(EXIT_SUCCESS);
	}else {
		if(editor->mode == NORMAL) normalModeHandler(editor, c);
		else if (editor->mode == INSERT) insertModeHandler(editor, c);
	}
}
