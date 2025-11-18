#pragma once

#include <termios.h>

static struct termios orig;

void enableRawMode();
void disableRawMode();
