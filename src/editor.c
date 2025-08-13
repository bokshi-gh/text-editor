#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "editor.h"

void init_editor(Editor *e) {
    e->num_lines = 1;
    e->cursor_x = 0;
    e->cursor_y = 0;
    e->mode = NORMAL;
    e->buffer[0][0] = '\0';
}

void insert_char(Editor *e, char c) {
    if (e->cursor_y >= e->num_lines) return; // safety check
    char *line = e->buffer[e->cursor_y];
    int len = strlen(line);
    if (len >= MAX_LINE_LEN - 1) return; // avoid overflow
    memmove(&line[e->cursor_x + 1], &line[e->cursor_x], len - e->cursor_x + 1);
    line[e->cursor_x] = c;
    e->cursor_x++;
}

void backspace(Editor *e) {
    if (e->cursor_x == 0) return;
    char *line = e->buffer[e->cursor_y];
    int len = strlen(line);
    memmove(&line[e->cursor_x - 1], &line[e->cursor_x], len - e->cursor_x + 1);
    e->cursor_x--;
}

void newline(Editor *e) {
    if (e->num_lines >= MAX_LINES - 1) return;
    char *line = e->buffer[e->cursor_y];
    strcpy(e->buffer[e->cursor_y + 1], &line[e->cursor_x]);
    line[e->cursor_x] = '\0';
    e->cursor_y++;
    e->cursor_x = 0;
    e->num_lines++;
}

void refresh_screen(Editor *e) {
    write(STDOUT_FILENO, "\x1b[2J", 4); // clear screen
    write(STDOUT_FILENO, "\x1b[H", 3);  // move cursor top-left

    for (int i = 0; i < e->num_lines; i++) {
        write(STDOUT_FILENO, e->buffer[i], strlen(e->buffer[i]));
        write(STDOUT_FILENO, "\r\n", 2);
    }

    char buf[32];
    snprintf(buf, sizeof(buf), "\x1b[%d;%dH", e->cursor_y + 1, e->cursor_x + 1);
    write(STDOUT_FILENO, buf, strlen(buf));
}

