#include <asm-generic/ioctls.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "terminal.h"

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

int get_terminal_height(){
	struct winsize w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1){
		perror("ioctl");
		exit(EXIT_FAILURE);
	}

	// w.ws_row => number of rows
	// w.ws_col => number of columns

	return w.ws_row;
}
