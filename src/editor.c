#include "unistd.h"
#include <stdio.h>
#include "../include/editor.h"
#include "../include/terminal.h"

Editor initEditor(){
	Editor editor = { .row = 0, .column = 0, .mode = NORMAL};
	for(int i =0; i < COLUMN_SIZE; i++){
		editor.buffer[i] = NULL;
	}
	editor.buffer[0] = "puta madre\0";
	editor.buffer[1] = "hello, world\0";
	return editor;
}

void renderBuffer(Editor *editor){
	clearTerminal();
	moveCursorHome();
	
	for (int i = 0; i < COLUMN_SIZE; i++) {
		char *row = editor->buffer[i];
		if(row){
			write(STDOUT_FILENO, row, sizeof(row));
			write(STDOUT_FILENO, "\n", 1);
		}
	}

	char cursor[100];
	sprintf(cursor, "\x1b[%d;%dH", editor->row, editor->column);
	write(STDOUT_FILENO, cursor, 6);
}
