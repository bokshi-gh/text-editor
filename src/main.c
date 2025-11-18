#include "../include/terminal.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	enableRawMode();

	char c;
	while (c != 'q') {
		read(STDIN_FILENO, &c, 1);
		write(STDOUT_FILENO, &c, 1);
	}

	return EXIT_SUCCESS;
}
