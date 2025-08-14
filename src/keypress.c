#include <stdlib.h>
#include <string.h>
#include "keypress.h"
#include "editor.h"

// make a struct for key

void process_keypress(Editor *e, char c){
	// backspace and newline
	// command mode, visual mode, normal mode, insert mode
	switch (e->mode) {
		case NORMAL:
			if(c == 'i') e->mode = INSERT;
			else if(c == 'q'){
				memset(e->buffer, 0, sizeof(e->buffer));
				refresh_screen(e);
				exit(0);
			}
			else if(c == 127) backspace_normal_mode(e);
		        break;
		case INSERT:
			if(c == 27) e->mode = NORMAL;
			if(c == 127) backspace_insert_mode(e);
			else{
				insert_char(e, c);
			}
			break;
	}
}
