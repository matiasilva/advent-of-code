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
#define PART1 1

typedef struct {
  size_t elems;
  int levels[TOK_MAX];
  bool is_safe;
} report;

void print_list(int levels[], size_t elems) {
  for (int i = 0; i < elems; i++) {
    printf("%i ", levels[i]);
  }
  puts("");
}
bool is_safe(int levels[TOK_MAX], size_t elems) {
  int n_diffs = elems - 1;
  int diffs[n_diffs];
  for (int j = 0; j < n_diffs; ++j) {
    diffs[j] = levels[j] - levels[j + 1];
  }
  /* check conditions */
  int is_pos_cnt = 0;
  int is_in_range_cnt = 0;
  for (int j = 0; j < n_diffs; ++j) {
    if (diffs[j] >= 0)
      is_pos_cnt++;
    if ((abs(diffs[j]) < 4) && (abs(diffs[j]) > 0)) {
      is_in_range_cnt++;
    }
  }
  return ((is_pos_cnt < 1) || (is_pos_cnt > (n_diffs - 1))) &&
         (is_in_range_cnt > (n_diffs - 1));
}

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
    r->is_safe = is_safe(r->levels, r->elems);
#ifndef PART1
    if (!r->is_safe) {
      // try removing one, see what happens
      int levels2[TOK_MAX];
      for (int j = 0; j < r->elems; ++j) {
        int elems2 = r->elems - 1;
        // printf("report: %d j: %d ", i, j);
        memcpy(levels2, r->levels, sizeof(int) * j);
        memcpy(&levels2[j], &(r->levels[j + 1]), sizeof(int) * (elems2 - j));
        // print_list(levels2, elems2);
        r->is_safe = is_safe(levels2, elems2);
        if (r->is_safe)
          break;
      }
    }
#endif
  }

  int safe = 0;
  for (int j = 0; j < REPORT_MAX; ++j) {
    safe += (int)reports[j].is_safe;
  }
  printf("safe: %d\n", safe);
  return EXIT_SUCCESS;
}
