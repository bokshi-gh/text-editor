#pragma once

#define MAX_LINES 1000
#define MAX_LINE_LEN 1024

enum Mode { NORMAL, INSERT, COMMAND, VISUAL };
enum Key { KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT };

typedef struct {
	char buffer[MAX_LINES][MAX_LINE_LEN];
	int num_lines;
	int cursor_x;
	int cursor_y;
	enum Mode mode;
} Editor;

void init_editor(Editor *e);
void insert_char(Editor *e, char c);
void backspace_insert_mode(Editor *e);
void backspace_normal_mode(Editor *e);
void newline(Editor *e);
void refresh_screen(Editor *e);
void arrow_key_handler(Editor *e, enum Key);
