#pragma once
#define ROW_SIZE 4096
#define COLUMN_SIZE 4096

typedef enum {
	NORMAL,
	INSERT,
	VISUAL,
	COMMAND
} EditorMode ;

typedef struct {
	int row;
	int column;
	char buffer[ROW_SIZE][COLUMN_SIZE];
	EditorMode mode;
} Editor;

Editor initEditor();
void renderBuffer(Editor *editor);
void normalModeHandler(Editor *editor, char c);
void insertModeHandler(Editor *editor, char c);

