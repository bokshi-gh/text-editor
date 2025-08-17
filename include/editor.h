#pragma once

#define MAX_LINES 1000
#define MAX_LINE_LEN 1024

enum Mode { NORMAL, INSERT, COMMAND, VISUAL };

typedef struct {
	char buffer[MAX_LINES][MAX_LINE_LEN];
	char old_buffer[MAX_LINES][MAX_LINE_LEN];
	char command_buffer[20];
	char filename[10];
	int num_lines;
	int cursor_x;
	int cursor_y;
	int row_offset;
	int col_offset;
	enum Mode mode;
} Editor;

void init_editor(Editor *e);
void backspace_normal_mode(Editor *e);
void backspace_insert_mode(Editor *e);
void newline_normal_mode(Editor *e);
void newline_insert_mode(Editor *e);
void insert_char(Editor *e, char c);
void refresh_screen(Editor *e);
