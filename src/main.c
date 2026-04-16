#include "terminal.h"
#include "editor.h"

#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  switch_to_alternate_screen_buffer();
  enable_raw_mode();

  // Important: atexit() executes functions in reverse order (LIFO)
  atexit(return_to_main_screen_buffer);
  atexit(disable_raw_mode);

  while (1) { 
    refress_screen();
    process_keypress();
  }

  return 0;
}
