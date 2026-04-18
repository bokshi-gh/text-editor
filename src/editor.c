#include "editor.h"

static Editor e;

void init_editor() {
  if (get_window_size(&e.rows, &e.cols) == -1) die("get_window_size");

  e.cx = 0;
  e.cy = 0;

  e.filename[0] = '\0';
  e.buffer = NULL;
  e.buffer_length = 0;

  e.gutter_width = snprintf(NULL, 0, "%d", e.rows) + 2;
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
  e.buffer = NULL;
  e.buffer_length = 0;
}

void update_cursor_position(int key) {
  switch (key) {
    case ARROW_LEFT:
      if (e.cx != 0) {
        e.cx--;
      }
      break;
    case ARROW_RIGHT:
      if (e.cx != e.cols - 1) {
        e.cx++;
      }
      break;
    case ARROW_UP:
      if (e.cy != 0) {
        e.cy--;
      }
      break;
    case ARROW_DOWN:
      if (e.cy != e.rows - 1) {
        e.cy++;
      }
      break;
  }
}

void draw_rows() {
  for (int y = 0; y < e.rows; y++) {

    char buf[32];

    // line number
    int len = snprintf(buf, sizeof(buf), "%*d ", e.gutter_width - 2, y + 1);
    buffer_append(buf, len);

    buffer_append("|", 1);   // separator
    buffer_append(" ", 1);   // spacing

    if (y < e.rows - 1) {
      buffer_append("\r\n", 2);
    }
  }
}

void refresh_screen() {
  buffer_append("\x1b[2J", 4);   // clear
  buffer_append("\x1b[H", 3);    // home

  draw_rows();

  char buf[32];
  int len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", e.cy + 1, e.cx + 1);
  buffer_append(buf, len);

  write(STDOUT_FILENO, e.buffer, e.buffer_length);
  buffer_free();
}

int read_key() {
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
      if (seq[1] >= '0' && seq[1] <= '9') {
        if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
        if (seq[2] == '~') {
          switch (seq[1]) {
            case '1': return HOME;
            case '4': return END;
            case '3': return DELETE;
            case '5': return PAGE_UP;
            case '6': return PAGE_DOWN;
            case '7': return HOME;
            case '8': return END;
          }
        }
      } else {
        switch (seq[1]) {
          case 'A': return ARROW_UP;
          case 'B': return ARROW_DOWN;
          case 'C': return ARROW_RIGHT;
          case 'D': return ARROW_LEFT;
          case 'H': return HOME;
          case 'F': return END;
        }
      }
    } else if (seq[0] == 'O') {
      switch (seq[1]) {
        case 'H': return HOME;
        case 'F': return END;
      }
    }

    return '\x1b';
  } else {
    return c;
  }
}

void process_keypress() {
  int c = read_key();

  switch (c) {
    case CTRL_KEY('q'):
      clear_entire_screen();
      move_cursor_to_home();
      exit(0);
      break;

    case HOME:
      e.cx = 0;
      break;
    case END:
      e.cx = e.cols - 1;
      break;

    case PAGE_UP:
    case PAGE_DOWN:
      {
        int times = e.rows;
        while (times--)
          update_cursor_position(c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
      }
      break;


    case ARROW_LEFT:
    case ARROW_RIGHT:
    case ARROW_UP:
    case ARROW_DOWN:
      update_cursor_position(c);
      break;
  }
}
