#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_WITH_MSG(format, ...)                                             \
  fprintf(stderr, format, ##__VA_ARGS__);                                      \
  exit(EXIT_FAILURE);

#define BUF_MAX 1000

int main(void) {
  /* read in file */
  FILE *file = fopen("d1p1.txt", "r");
  if (!file) {
    EXIT_WITH_MSG("unable to open input file\n");
  }

  return EXIT_SUCCESS;
}
