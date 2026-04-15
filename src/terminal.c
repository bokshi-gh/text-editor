#include "terminal.h"

void switch_to_alternate_screen_buffer() { write(STDOUT_FILENO, "\x1b[?1049h", 8); }

void return_to_main_screen_buffer() { write(STDOUT_FILENO, "\x1b[?1049l", 8); }
