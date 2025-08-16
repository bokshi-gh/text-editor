#include <termios.h>
#include <unistd.h>
#include "termios_config.h"
#include "editor.h"
#include "keypress.h"

int main(int argc, char *argv[]) {
  enable_raw_mode();

  Editor e;
  init_editor(&e);

  refresh_screen(&e);

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1) {
	process_keypress(&e, c);
    refresh_screen(&e);
  }

  return 0;
}
