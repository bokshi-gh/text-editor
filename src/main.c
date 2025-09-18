#include "../include/editor.h"
#include "../include/keypress.h"
#include "../include/terminal.h"
#include <unistd.h>
#include <stdbool.h>

int main(void) {
  enableAlternateBuffer();
  enableRawMode();

  Editor editor = initEditor();

  while (true) {
    renderBuffer(&editor);
    handleKeyPress(&editor);
  }

  return 0;
}
