#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_WITH_MSG(format, ...)                                             \
  fprintf(stderr, format, ##__VA_ARGS__);                                      \
  exit(EXIT_FAILURE);

#define BUF_MAX 128
#define TOK_MAX 8
#define REPORT_MAX 1000

typedef struct {
  size_t elems;
  int levels[TOK_MAX];
  bool is_safe;
} report;

int main(void) {
  /* read in file */
  FILE *file = fopen("d2.txt", "r");
  if (!file) {
    EXIT_WITH_MSG("unable to open input file\n");
  }

  report reports[REPORT_MAX];
  char line_buf[BUF_MAX];
  int i = 0;

  /* load in reports */
  while (fgets(line_buf, sizeof(line_buf), file)) {
    report r = {.elems = 0, .is_safe = false};
    char *token = strtok(line_buf, " ");
    while (token != NULL) {
      r.levels[r.elems] = strtol(token, NULL, 10);
      r.elems++;
      token = strtok(NULL, " ");
    }
    reports[i] = r;
    i++;
  }

  /* calculate diffs */
  for (int i = 0; i < REPORT_MAX; ++i) {
    report *r = &reports[i];
    int n_diffs = r->elems - 1;
    int diffs[n_diffs];
    for (int j = 0; j < n_diffs; ++j) {
      diffs[j] = r->levels[j] - r->levels[j + 1];
    }
    /* check conditions */
    bool is_pos = diffs[0] >= 0;
    int bad = 0;
    for (int j = 0; j < n_diffs; ++j) {
      bad |= (diffs[j] >= 0) != is_pos;
      bad |= abs(diffs[j]) > 3 || abs(diffs[j]) < 1;
    }
    r->is_safe = !bad;
  }

  int safe = 0;
  for (int j = 0; j < REPORT_MAX; ++j) {
    safe += (int)reports[j].is_safe;
  }
  printf("safe: %d\n", safe);
  return EXIT_SUCCESS;
}
