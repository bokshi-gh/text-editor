#include <stdlib.h>
#include <string.h>
#include "keypress.h"
#include "editor.h"

void process_keypress(Editor *e, char c){
	switch (e->mode) {
		case NORMAL:
			if(c == 'i') e->mode = INSERT;
		        break;
		case INSERT:
			if(c == 27) e->mode = NORMAL;
			else{
				e->buffer[e->cursor_x][e->cursor_y] = c;
			}
			break;
		case 'q':
			exit(0);
	}
}
