#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_WITH_MSG(format, ...)                                             \
  fprintf(stderr, format, ##__VA_ARGS__);                                      \
  exit(EXIT_FAILURE);

#define BUF_MAX 1000
#define CHUNK_MAX 4000
#define SEARCH_STR "mul("

int main(void) {
  /* read in file */
  FILE *file = fopen("d3.txt", "r");
  if (!file) {
    EXIT_WITH_MSG("unable to open input file\n");
  }
  char chunk[CHUNK_MAX];
  int acc = 0;
  int ctr = 0;
  while (fgets(chunk, sizeof(chunk), file)) {
    for (int i = 0; i < sizeof(chunk); i++) {
      if (chunk[i] == '\0')
        break;
      char *s = strstr(&chunk[i], SEARCH_STR);
      if (s != NULL) {
        int a = 0, b = 0, n = 0;
        if (sscanf(s + strlen(SEARCH_STR), "%d,%d)%n", &a, &b, &n) == 2 &&
            n != 0) {
          // printf("%s\n%s\n%d %d %d\n\n", s, &chunk[i], a, b, n);
          // printf("mul(%d,%d)\n", a, b);
          if (a == 653) {
            puts("hi");
          }
          acc += a * b;
          i += n + strlen(SEARCH_STR) + (s - &chunk[i]) - 1;
          if (a == 41 && b == 963) {
            printf("%s\n", &chunk[i]);
          }
          ctr++;
        }
      }
    }
  }

  printf("total mul: %d\n", acc);
  printf("total ctr: %d\n", ctr);

  return EXIT_SUCCESS;
}
