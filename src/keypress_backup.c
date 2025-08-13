#include <stdlib.h>
#include "keypress.h"
#include "editor.h"

void process_keypress(Editor *e, char c){
	switch (c) {
		case 127:
			backspace(e);
		        break;
		case '\r':
			newline(e);
			break;
		case 'q':
			exit(0);
	}
}
