#include <stdio.h>
#include <stdlib.h>
#include "../include/keypress.h"
#include "../include/editor.h"
#include "../include/terminal.h"

void handleKeyPress(Editor *editor, char c){
	if (c == 'q') {
		disableAlternateBuffer();
		exit(EXIT_SUCCESS);
	}

        if (c < 32) {
            printf("%d\n", c);  // control char
        } else {
            printf("%c (%d)\n", c, c);
        }
}
