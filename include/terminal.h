#ifndef TERMINAL_H
#define TERMINAL_H

#include "errors.h"

#include <termios.h>
#include <unistd.h>

void switch_to_alternate_screen_buffer();
void return_to_main_screen_buffer();

void enable_raw_mode();
void disable_raw_mode();

#endif
