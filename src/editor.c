#include "unistd.h"
#include <string.h>
#include "../include/editor.h"

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
	for (int i = 0; i < COLUMN_SIZE; i++) {
		char *row = editor->buffer[i];
		if(row){
			write(STDOUT_FILENO, row, sizeof(row));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}
