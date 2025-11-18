#include "../include/terminal.h"
#include <unistd.h>

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

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
}

