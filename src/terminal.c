#include "../include/terminal.h"
#include <unistd.h>

void enter_alternate_screen_buffer() { write(STDOUT_FILENO, "\x1b[1049h", 8); }

void leave_alternate_screen_buffer() { write(STDOUT_FILENO, "\x1b[1049l", 8); }

void enableRawMode() {
  tcgetattr(STDIN_FILENO, &orig);

  struct termios raw = orig;

  // Input flags: turn off canonical mode, echoing, and signal chars
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  // Input modes: disable CR -> NL translation, disable software flow ctrl
  raw.c_iflag &= ~(ICRNL | IXON | BRKINT | INPCK | ISTRIP);

  // Output modes: disable post-processing
  raw.c_oflag &= ~(OPOST);

  // Control modes: set character size to 8 bits per byte
  raw.c_cflag |= (CS8);

  // Make reads return after 1 byte or 0.1 seconds
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig); }

void move_cursor_up() {
	write(STDOUT_FILENO, "\x1b[A", 3);
}

void move_cursor_down() {
	write(STDOUT_FILENO, "\x1b[B", 3);
}

void move_cursor_right() {
	write(STDOUT_FILENO, "\x1b[C", 3);
}

void move_cursor_left() {
	write(STDOUT_FILENO, "\x1b[D", 3);
}

void move_cursor_to_home() {
	write(STDOUT_FILENO, "\x1b[H", 3);
}

void clear_terminal() {
	write(STDOUT_FILENO, "\x1b[2J", 4);
}
