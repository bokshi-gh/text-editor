#include "errors.h"

void die(const char *mes) {
  perror(mes);
  exit(1);
}
