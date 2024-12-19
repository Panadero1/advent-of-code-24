#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_SIZE 20000

static int find_pattern(char* buf, int len, int off, char* pattern) {
  int prog = 0;

  int plen = strlen(pattern);

  for (int i = off + plen; i < len; i++) {
    if (strncmp(buf + i - plen, pattern, plen) == 0) {
      return i - plen;
    }
  }

  return -1;
}

static int get_num(char* buf, int len, int off, int max_digit, int* dig_out) {
  int resnum = 0;
  *dig_out = 0;

  for (int i = 0; i < max_digit; i++) {
    if (i + off > len) { 
      return -1;
    }
    char c = buf[i + off];
    if (c > '9' || c < '0') {
      if (i == 0) {
        return -1;
      } else {
        break;
      }
    }

    resnum = resnum * 10 + c - '0';
    *dig_out = *dig_out + 1;
  }

  return resnum;
}

static int find_next_mul(char* buf, int len, int offset, int* tot) {
  int pat_idx = -1;
  int i_off = offset;
  
  bool found = false;

  while ((pat_idx = find_pattern(buf, len, i_off, "mul(")) != -1) {
    i_off = pat_idx + 1;

    int d1;
    int n1 = get_num(buf, len, pat_idx + 4, 3, &d1);
    
    if (n1 == -1) {
      continue;
    }

    if (buf[pat_idx + 4 + d1] != ',') {
      continue;
    }

    int d2;
    int n2 = get_num(buf, len, pat_idx + 5 + d1, 3, &d2);

    if (n2 == -1) {
      continue;
    }

    if (buf[pat_idx + 5 + d1 + d2] != ')') {
      continue;
    }

    *tot = n1 * n2;
    found = true;
    break;
  }

  if (!found) {
    return -1;
  }

  return pat_idx;
}

static void part_1() {
  FILE* file = fopen("../input/day3.txt", "r");

  int total = 0;

  char buf[FILE_SIZE];

  int l = fread(buf, 1, FILE_SIZE, file);

  int offset = 0;
  int pat_idx;

  int par_tot;

  while ((pat_idx = find_next_mul(buf, l, offset, &par_tot)) != -1) {
    offset = pat_idx + 1;

    total += par_tot;
  }
  
  fclose(file);

  printf("part 1: %d\n", total);
}

static void part_2() {
  FILE* file = fopen("../input/day3.txt", "r");

  char buf[FILE_SIZE];

  int l = fread(buf, 1, FILE_SIZE, file);

  int total = 0;

  int next_dont = find_pattern(buf, l, 0, "don't()");

  int par_tot;
  int pat_idx;
  int offset = 0;

  while ((pat_idx = find_next_mul(buf, l, offset, &par_tot)) != -1) {
    offset = pat_idx + 1;
    if (pat_idx > next_dont) {
      int old_next_dont = next_dont;
      next_dont = find_pattern(buf, l, next_dont + 1, "don't()");

      if (next_dont == -1) {
        next_dont = l + 4;
      }

      offset = find_pattern(buf, l, old_next_dont + 1, "do()");

      if (offset == -1) {
        break;
      }
    } else {
      total += par_tot;
    }
  }

  fclose(file);

  printf("part 2: %d\n", total);
}

int main() {
  part_1();
  part_2();

  return EXIT_SUCCESS;
}
