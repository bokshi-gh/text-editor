#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/keypress.h"
#include "../include/editor.h"
#include "../include/terminal.h"

void handleKeyPress(Editor *editor, char c){
	moveCursor(HOME);
	if (c == 'q') {
		disableAlternateBuffer();
		exit(EXIT_SUCCESS);
	}

	if(c == 'k'){
		moveCursor(UP);
		return;
	}

	if(c == 'j'){
		moveCursor(DOWN);
		return;
	}

	if(c == 'l'){
		moveCursor(RIGHT);
		return;
	}

	if(c == 'h'){
		moveCursor(LEFT);
		return;
	}

	if(c != ' '){
		strcat(editor->buffer[0], &c);
		return;
	}

        //if (c < 32) {
            //printf("%d\n", c);  // control char
        //} else {
            //printf("%c (%d)\n", c, c);
        //}
}
