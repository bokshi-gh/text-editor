#pragma once

#include <termios.h>

static struct termios orig;

void enter_alternate_screen_buffer();
void leave_alternate_screen_buffer();

void enableRawMode();
void disableRawMode();

void move_cursor(unsigned int row, unsigned int column);
void move_cursor_up();
void move_cursor_down();
void move_cursor_right();
void move_cursor_left();
void move_cursor_to_home();

void clear_terminal();
