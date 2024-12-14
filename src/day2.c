#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static int line_of_levels(int* levels, FILE* file) {
  int i = 0;
  while (1) {
    int n;
    char c;
    if (fscanf(file, "%d%c", &n, &c) == EOF) {
      break;
    }

    levels[i] = n;
    i++;
    if (c == '\n') {
      break; 
    }

  }
  return i;
}

static bool is_safe(int* levels, int nl, int skip) {
  bool safe = true;
  bool inc = true;
  bool dec = true;
  int last;
  int i;
  if (skip == 0) {
    last = levels[1];
    i = 2;
  } else {
    last = levels[0];
    i = 1;
  }

  for (; i < nl; i++) {
    if (i == skip) {
      continue;
    }
    if (abs(last - levels[i]) > 3) {
      safe = false;
      break;
    }
    if (levels[i] > last) {
      dec = false;
    } else if (levels[i] < last) {
      inc = false;
    } else {
      safe = false;
      break;
    }
    last = levels[i];
  }

  if (!inc && !dec) {
    safe = false;
  }
  return safe;
}

static void part_1() {
  int levels[8];

  FILE* file = fopen("../input/day2.txt", "r");

  if (file == NULL) {
    printf("null file\n");
  }

  int n_safe = 0;

  while (1) {
    int nl = line_of_levels(levels, file);

    if (nl == 0) {
      break;
    }

    if (is_safe(levels, nl, -1)) {
      n_safe++;
    }
  }

  printf("part 1: %d\n", n_safe);

  fclose(file);
}

static void part_2() {
  int levels[8];

  FILE* file = fopen("../input/day2.txt", "r");

  int n_safe = 0;

  while (1) {
    int nl = line_of_levels(levels, file);

    if (nl == 0) {
      break;
    }

    bool safe = false;

    for (int i = 0; i < nl; i++) {
      if (is_safe(levels, nl, i)) {
        safe = true;
        break;
      }
    }

    if (safe) {
      n_safe++;
    }

  }
  printf("part 2: %d\n", n_safe);

  fclose(file);
}

int main() {
  part_1();
  part_2();

  return EXIT_SUCCESS;
}
