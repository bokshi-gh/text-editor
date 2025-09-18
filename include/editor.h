#pragma once

typedef enum {
	NORMAL,
	INSERT,
	VISUAL,
	COMMAND
} EditorMode ;

typedef struct {
	int row;
	int column;
	char *buffer;
	EditorMode mode;
} Editor;

Editor initEditor();
void renderBuffer(Editor *editor);
void normalModeHandler(Editor *editor, char c);
void insertModeHandler(Editor *editor, char c);

