#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "terminal.h"
#include "editor.h"
#include "keypress.h"

int main(int argc, char *argv[]) {
    enable_raw_mode();

    Editor e;
    init_editor(&e);
    refresh_screen(&e);

    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (file) {
            while (e.num_lines < 1000 && fgets(e.buffer[e.num_lines], 1024, file)) {
                char *newline = strchr(e.buffer[e.num_lines], '\n');
                if (newline) *newline = '\0';
                e.num_lines++;
            }
	    memcpy(e.filename, argv[1], sizeof(argv[1]));
            fclose(file);
        } else {
            perror("fopen");
        }
    }

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1) {
        process_keypress(&e, c);
        refresh_screen(&e);
    }

    return 0;
}

