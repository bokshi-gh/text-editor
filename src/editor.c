#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "editor.h"
#include "terminal.h"

void init_editor(Editor *e) {
	e->buffer[0][0] = '\0';
	e->old_buffer[0][0] = '\0';
	e->command_buffer[0] = '\0';
	e->filename[0] = '\0';
	e->num_lines = 0;
	e->cursor_x = 0;
	e->cursor_y = 0;
	e->row_offset = 0;
	e->col_offset = 0;
	e->mode = NORMAL;
}

void insert_char(Editor *e, char c){
	if (e->cursor_y >= e->num_lines) return; // safety check
	char *line = e->buffer[e->cursor_y];
        int len = strlen(line);
        if (len >= MAX_LINE_LEN - 1) return; // avoid overflow
        memmove(&line[e->cursor_x + 1], &line[e->cursor_x], len - e->cursor_x + 1);
        line[e->cursor_x] = c;
        e->cursor_x++;
}

void backspace_normal_mode(Editor *e){
	e->cursor_x--;
}

void backspace_insert_mode(Editor *e){
	char *line = e->buffer[e->cursor_y];
	int len = strlen(line);
	memmove(&line[e->cursor_x-1], &line[e->cursor_x], len - e->cursor_x+1);
	e->cursor_x--;
}

void newline_normal_mode(Editor *e){
	e->cursor_y++;
}

void newline_insert_mode(Editor *e) {
    if (e->num_lines >= MAX_LINES) return;

    for (int i = e->num_lines; i > e->cursor_y; i--) {
        strcpy(e->buffer[i], e->buffer[i-1]);
    }

    char *line = e->buffer[e->cursor_y];
    int len = strlen(line);

    strcpy(e->buffer[e->cursor_y + 1], &line[e->cursor_x]);

    line[e->cursor_x] = '\0';

    e->num_lines++;
    e->cursor_y++;
    e->cursor_x = 0;
}


void refresh_screen(Editor *e) {
    write(STDOUT_FILENO, "\x1b[2J", 4); // clear screen
    write(STDOUT_FILENO, "\x1b[H", 3);  // move cursor top-left
    
    for (int i = e->row_offset; i < e->num_lines; i++) {
        write(STDOUT_FILENO, e->buffer[i], strlen(e->buffer[i]));
        write(STDOUT_FILENO, "\r\n", 2);
    }

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", e->cursor_y + 1, e->cursor_x + 1);
    write(STDOUT_FILENO, buf, strlen(buf));
}
