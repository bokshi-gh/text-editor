#include "editor.h"

void init_editor(Editor e) {
  if (get_window_size(&e.rows, &e.cols) == -1) die("get_window_size");
}

void draw_rows() {
  int y;

  for (y = 0; y < 24; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}

void refresh_screen() {
  clear_entire_screen();
  move_cursor_to_home();

  draw_rows();

  move_cursor_to_home();
}

char read_key() {
  int nread;
  char c;

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }

  return c;
}

void process_keypress() {
  char c = read_key();

  switch (c) {
    case CTRL_KEY('q'):
      exit(0);
      break;
  }
}
