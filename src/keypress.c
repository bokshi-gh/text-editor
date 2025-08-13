#include <stdlib.h>
#include <string.h>
#include "keypress.h"
#include "editor.h"

void process_keypress(Editor *e, char c){
	// backspace and newline
	// command mode, visual mode, normal mode, insert mode
	switch (e->mode) {
		case NORMAL:
			if(c == 'i') e->mode = INSERT;
			else if(c == 'q') exit(0);
		        break;
		case INSERT:
			if(c == 27) e->mode = NORMAL;
			else{
				insert_char(e, c);
			}
			break;
	}
}
