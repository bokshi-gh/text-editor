#pragma once
#define ROW_SIZE 1049
#define COLUMN_SIZE 1049

typedef enum {
	NORMAL,
	INSERT,
	VISUAL,
	COMMAND
} EditorMode ;

typedef struct {
	int x;
	int y;
	char buffer[ROW_SIZE][COLUMN_SIZE];
	EditorMode mode;
} Editor;

Editor initEditor();
