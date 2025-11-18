#pragma once

typedef enum { NORMAL, INSERT } Mode;

typedef struct {
	char *buffer;
	Mode mode;

} Editor;
