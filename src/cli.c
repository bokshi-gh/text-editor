#include "cli.h"

void show_version() { printf("%s %s\n", TARGET, VERSION); }

void show_unknown(char *argv[]) {
  printf("%s: unknown option %s'%s'%s\n", TARGET, ANSI_GREEN, argv[1], ANSI_RESET);
  printf("Try %s'%s --help'%s for more information.\n", ANSI_GREEN, TARGET, ANSI_RESET);
}

void handle_cli(int argc, char *argv[]) {
  if (argc == 1) {
    return;
  } else if (argc == 2) {
    if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--info") == 0) {
      // show_info();
    } else  if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
      show_version();
    } else  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
      // show_help();
    }
  } else {
    show_unknown(argv);
  }

  exit(1);
}
