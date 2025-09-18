#include "../include/editor.h"
#include "../include/terminal.h"

Editor initEditor(){
	Editor editor = { .row = 1, .column = 1, .mode = NORMAL};
	return editor;
}

void renderBuffer(Editor *editor){
	clearTerminal();
	moveCursor(1, 1);
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
