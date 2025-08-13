#include <termios.h>
#include <unistd.h>
#include "termios_config.h"
#include "editor.h"

int main(int argc, char *argv[]) {
  enable_raw_mode();

  Editor e;
  init_editor(&e);

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1) {
    if (c == 127)
      backspace(&e);
    else if (c == )
    else if (c == '\r')
      newline(&e);
    else
      insert_char(&e, c);
    refresh_screen(&e);
  }

  return 0;
}
