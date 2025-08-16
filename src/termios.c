#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "termios.h"

struct termios orig_termios;

void disable_raw_mode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); }

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  atexit(disable_raw_mode);

  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON | ISIG); // no echo, no buffering, no signals
  raw.c_iflag &= ~(IXON);                 // disable Ctrl-S/Ctrl-Q
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
