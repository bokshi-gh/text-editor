#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "editor.h"

void process_keypress(Editor *e, char c){
    switch (e->mode) {
        case NORMAL:
            if(c == 'i') {
                e->mode = INSERT;
            }
            else if(c == 'q'){
		if(sizeof(e->old_buffer) != 0){
					memcpy(e->buffer, e->old_buffer, sizeof(e->old_buffer));
					memset(e->old_buffer, 0, sizeof(e->old_buffer));
					return;
		}
                memset(e->buffer, 0, sizeof(e->buffer));
                e->cursor_x = 0;
                e->cursor_y = 0;
                refresh_screen(e);
                exit(0);
            }
            else if(c == 'h') {  // move left
                if(e->cursor_x > 0) e->cursor_x--;
            }
            else if(c == 'l') {  // move right
                if(e->cursor_x < strlen(e->buffer[e->cursor_y])) e->cursor_x++;
            }
            else if(c == 'k') {  // move up
                if(e->cursor_y > 0) {
                    e->cursor_y--;
                    if(e->cursor_x > strlen(e->buffer[e->cursor_y]))
                        e->cursor_x = strlen(e->buffer[e->cursor_y]);
                }
            }
            else if(c == 'j') {  // move down
                if(e->cursor_y < e->num_lines - 1) {
                    e->cursor_y++;
                    if(e->cursor_x > strlen(e->buffer[e->cursor_y]))
                        e->cursor_x = strlen(e->buffer[e->cursor_y]);
                }
            }
	    else if(c == 19) {  // Ctrl+S
                if(e->filename != NULL) {
                    FILE *file = fopen(e->filename, "w");
                    if(file) {
                        for(int i = 0; i < e->num_lines; i++) {
                            fprintf(file, "%s\n", e->buffer[i]);
                        }
                        fclose(file);
                        // Optionally show a message or refresh screen
                    } else {
                        perror("fopen");
                    }
                }
            }
	    else if(c == 'e'){
				DIR *d;
				struct dirent *dir;

				d = opendir(".");
				if(d) {
					e->num_lines = 0;
					memcpy(e->old_buffer, e->buffer, sizeof(e->buffer));
					memset(e->buffer, 0, sizeof(e->buffer));
					int i = 0;
					while ((dir = readdir(d)) != NULL) {
						memcpy(e->buffer[i++], dir->d_name, sizeof(dir->d_name));
						e->num_lines++;
					}
				}
				closedir(d);
	    }
            else if(c == 8 || c == 127) backspace_normal_mode(e);
            else if(c == 13) newline_normal_mode(e);
            else if(c == 8 || c == 127) backspace_normal_mode(e);
            else if(c == 13) newline_normal_mode(e);
            break;

        case INSERT:
            if(c == 27){  // ESC
                e->mode = NORMAL;
            }
            else if(c == 8 || c == 127) backspace_insert_mode(e);
            else if(c == 13) newline_insert_mode(e);
            else {
                insert_char(e, c);
            }
            break;
    }
}

