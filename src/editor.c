#include <string.h>
#include <unistd.h>
#include "../include/editor.h"
#include "../include/terminal.h"

Editor initEditor(){
	Editor editor = { .row = 1, .column = 1, .mode = NORMAL};
	editor.buffer[0][1] = 'a';
	editor.buffer[0][2] = 'a';
	editor.buffer[0][3] = 'a';
	return editor;
}

void renderBuffer(Editor *editor){
	clearTerminal();
	moveCursor(1, 1);

	int buffer_row_size = sizeof(editor->buffer);
	for (int i = 0; i < buffer_row_size; i++) {
		char *row = editor->buffer[i];
		write(STDOUT_FILENO, row, strlen(row));
	}

	moveCursor(editor->row, editor->column);
}

void normalModeHandler(Editor *editor, char c){
	if(c == 'i') editor->mode = INSERT;
	if(c == 'k') editor->row--;
	if(c == 'j') editor->row++;
	if(c == 'l') editor->column++;
}

void insertModeHandler(Editor *editor, char c){
	if(c == 27) editor->mode = NORMAL;
}
