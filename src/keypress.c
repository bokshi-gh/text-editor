#include <unistd.h>
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
			if(c == 27){
				char seq[2];
				if(read(STDIN_FILENO, &seq[0], 1) == 0) return;
				if(read(STDIN_FILENO, &seq[1], 1) == 0) return;

				if(seq[0] == '['){
					switch (seq[1]) {
						case 'A':
							arrow_key_handler(e, KEY_UP);
							break;
						case 'B':
							arrow_key_handler(e, KEY_DOWN);
							break;
						case 'C':
							arrow_key_handler(e, KEY_RIGHT);
							break;
						case 'D':
							arrow_key_handler(e, KEY_LEFT);
							break;


					}
				}
				else e->mode = NORMAL;
			}
			if(c == 127) backspace_insert_mode(e);
			else{
				insert_char(e, c);
			}
			break;
	}
}
