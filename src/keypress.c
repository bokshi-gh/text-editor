#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/keypress.h"
#include "../include/editor.h"
#include "../include/terminal.h"

void handleKeyPress(Editor *editor, char c){
	write(STDOUT_FILENO, "editor mode", 11);
	if (c == 'q') {
		disableAlternateBuffer();
		exit(EXIT_SUCCESS);
	}else {
		if(editor->mode == NORMAL){
			if(c == 'i') editor->mode = INSERT;
			if(c == 'k') editor->row -= 1;
			if(c == 'j') editor->row += 1;
			if(c == 'l') editor->column += 1;
			if(c == 'h') editor->column -= 1;

		}else if (editor->mode == INSERT) {
			if(c == 27) editor->mode = NORMAL;
			else write(STDOUT_FILENO, &c, 1);
		}
	}
}
