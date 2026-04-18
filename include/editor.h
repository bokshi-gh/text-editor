#ifndef EDITOR_H
#define EDITOR_H

#define TARGET "cvim"
#define VERSION "0.0.1"

#define CTRL_KEY(k) ((k) & 0x1f)

#include "errors.h"
#include "terminal.h"

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  NULL = 0,

  H = 'h',
  J = 'j',
  K = 'k',
  L = 'l',

  ARROW_UP = 1000,
  ARROW_DOWN,
  ARROW_LEFT,
  ARROW_RIGHT,

  ESC = 27
  COLON = ':'
} EditorKey;

typedef struct {
  int rows;
  int cols;

  int cx;
  int cy;

  char filename[256];
  char *buffer;
  int buffer_length;
} Editor;

void init_editor();

void set_filename(const char *filename);

void refresh_screen();

void process_keypress();

#endif
