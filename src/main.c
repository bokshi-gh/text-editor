#include "../include/terminal.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	enableRawMode();

	char *c;
	while(*c != 'q') {
		read(0, c, 1);
	}
	return EXIT_SUCCESS;
}
