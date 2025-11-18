#pragma once

#include <termios.h>

static struct termios orig;

void enableRawMode();
void disableRawMode();

void get_terminal_dimentions();

void move_cursor(unsigned int row, unsigned int column);
void move_cursor_up();
void move_cursor_down();
void move_cursor_right();
void move_cursor_left();
void move_cursor_to_home();

void clear_terminal();

void switch_to_main_buffer();
void switch_to_alternate_buffer();
