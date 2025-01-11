#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define EXIT_WITH_MSG(format, ...)                                             \
  fprintf(stderr, format, ##__VA_ARGS__);                                      \
  exit(EXIT_FAILURE);

#define BUF_MAX 1000

void insertion_sort(int list[], size_t len) {
  int ptr = 1;
  while (ptr != len) {
    bool greater = list[ptr] >= list[ptr - 1];
    if (greater) {
      ptr++;
    } else {
      int old_val = list[ptr - 1];
      list[ptr - 1] = list[ptr];
      list[ptr] = old_val;
      if (ptr > 1)
        ptr--;
    }
  }
}

int count_occurrences(int list[], size_t len, int val) {
  int cnt = 0;
  for (int j = 0; j < len; ++j) {
    if (list[j] == val) {
      cnt++;
    } else if (list[j] != val && cnt > 0) {
      break;
    }
  }
  return cnt;
}

int main(void) {
  /* read in file */
  FILE *file = fopen("d1p1.txt", "r");
  int list1[BUF_MAX], list2[BUF_MAX];
  if (!file) {
    EXIT_WITH_MSG("unable to open input file\n");
  }
  int line = 0;
  while (fscanf(file, "%i   %i\n", &list1[line], &list2[line]) == 2) {
    ++line;
  }

  insertion_sort(list1, BUF_MAX);
  insertion_sort(list2, BUF_MAX);

  int acc = 0;
  for (int i = 0; i < BUF_MAX; ++i) {
    acc += list1[i] > list2[i] ? list1[i] - list2[i] : list2[i] - list1[i];
  }

  /* part 2 */
  int acc2 = 0;
  for (int i = 0; i < BUF_MAX; ++i) {
    acc2 += list1[i] * count_occurrences(list2, BUF_MAX, list1[i]);
  }

  printf("total distance: %d\n", acc);
  printf("total similarity: %d\n", acc2);
  return EXIT_SUCCESS;
}
