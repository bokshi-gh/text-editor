#include "terminal.h"

struct termios orig_termios;

void switch_to_alternate_screen_buffer() { write(STDOUT_FILENO, "\x1b[?1049h", 8); }

void return_to_main_screen_buffer() { write(STDOUT_FILENO, "\x1b[?1049l", 8); }

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &orig_termios);

  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }
