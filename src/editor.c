#include "editor.h"

static Editor e;

void init_editor() {
  if (get_window_size(&e.rows, &e.cols) == -1) die("get_window_size");

  e.cx = 0;
  e.cy = 0;

  e.filename[0] = '\0';
  e.buffer = NULL;
  e.buffer_length = 0;
}

void set_filename(const char *filename) {
  strncpy(e.filename, filename, sizeof(e.filename) - 1);
  e.filename[sizeof(e.filename) - 1] = '\0';
}

void buffer_append(const char *s, int length) {
  char *new = realloc(e.buffer, e.buffer_length + length);

  if (new == NULL) return;
  memcpy(&new[e.buffer_length], s, length);
  e.buffer = new;
  e.buffer_length += length;
}

void buffer_free() {
  free(e.buffer);
}

void update_cursor_position(char key) {
  switch (key) {
    case 'h':
      e.cx--;
      break;
    case 'l':
      e.cx++;
      break;
    case 'k':
      e.cy--;
      break;
    case 'j':
      e.cy++;
      break;
  }
}

void draw_rows() {
  int y;

  for (y = 0; y < e.rows; y++) {
    buffer_append("~", 1);

    if (y < e.rows - 1) {
      buffer_append("\r\n", 2);
    }
  }
}

void refresh_screen() {
  clear_entire_screen();
  move_cursor_to_home();

  draw_rows();

  move_cursor(e.cx, e.cy);

  move_cursor_to_home();

  write(STDOUT_FILENO, e.buffer, e.buffer_length);
  buffer_free();
}

char read_key() {
  int nread;
  char c;

  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }

  if (c == '\x1b') {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';
    if (seq[0] == '[') {
      switch (seq[1]) {
        case 'A': return 'k';
        case 'B': return 'j';
        case 'C': return 'l';
        case 'D': return 'h';
      }
    }
    return '\x1b';
  } else {
    return c;
  }

  return c;
}

void process_keypress() {
  char c = read_key();

  switch (c) {
    case CTRL_KEY('q'):
      clear_entire_screen();
      move_cursor_to_home();
      exit(0);
      break;

    case 'h':
    case 'j':
    case 'k':
    case 'l':
      update_cursor_position(c);
      break;
  }
}
