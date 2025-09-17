#pragma once

typedef enum {
	HOME,
	UP,
	DOWN,
	RIGHT,
	LEFT
} CursorMovementPosition;

void disableRawMode(void);
void enableRawMode(void);
void enableAlternateBuffer();
void disableAlternateBuffer();
void clearTerminal();
void moveCursor(CursorMovementPosition position);
