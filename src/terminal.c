#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>

#include "../include/terminal.h"

static struct termios orig_termios;

void disableRawMode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(void) {
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        perror("tcgetattr");
        exit(1);
    }
    atexit(disableRawMode);

    struct termios raw = orig_termios;

    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        perror("tcsetattr");
        exit(1);
    }
}

void clearTerminal(){
	write(STDOUT_FILENO, "\x1b[2J", 4);
}

void enableAlternateBuffer(){
	write(STDOUT_FILENO, "\x1b[?1049h", 8);
}

void disableAlternateBuffer(){
	clearTerminal();
	write(STDOUT_FILENO, "\x1b[?1049l", 8);
}

void moveCursor(CursorMovementPosition position){
	switch (position) {
		case HOME:
			write(STDOUT_FILENO, "\x1b[H", 3);
		        break;
		case UP:
			write(STDOUT_FILENO, "\x1b[A", 3);
		        break;
		case DOWN:
			write(STDOUT_FILENO, "\x1b[B", 3);
		        break;
		case RIGHT:
			write(STDOUT_FILENO, "\x1b[C", 3);
		        break;
		case LEFT:
			write(STDOUT_FILENO, "\x1b[D", 3);
		        break;
	}
}
