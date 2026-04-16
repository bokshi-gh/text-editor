#ifndef EDITOR_H
#define EDITOR_H

#define CTRL_KEY(k) ((k) & 0x1f)

#include "errors.h"

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

char read_key();
void process_keypress();

#endif
