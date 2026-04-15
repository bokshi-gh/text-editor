#include "terminal.h"

struct termios orig_termios;

void switch_to_alternate_screen_buffer() { write(STDOUT_FILENO, "\x1b[?1049h", 8); }

void return_to_main_screen_buffer() { write(STDOUT_FILENO, "\x1b[?1049l", 8); }

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &orig_termios);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO);

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }
