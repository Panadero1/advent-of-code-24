#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static int fill_lists(int** p_list1, int** p_list2) {
  FILE* file = fopen("../input/day1.txt", "r");

  // count lines
  int lc = 0;
  while (1) {
    int c = fgetc(file);
    if (c == EOF) {
      break;
    }
    if (c == '\n') {
      lc++;
    }
  }

  rewind(file);

  *p_list1 = (int*) malloc(sizeof(int) * lc);
  *p_list2 = (int*) malloc(sizeof(int) * lc);

  // extract two lists (in code)
  for (int i = 0; i < lc; i++) {
    fscanf(file, "%d   %d\n", (*p_list1 + i), (*p_list2 + i));
  }
  fclose(file);

  return lc;
}

static void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// quick sort algorithm
static void sort(int* list, int n) {
  // base cases
  if (n == 1) {
    //printf("sorting 1! %d\n", list[0]);
    return;
  }
  if (n == 2) {
    //printf("sorting 2! %d %d\n", list[0], list[1]);
    if (list[0] > list[1]) {
      swap(&list[0], &list[1]);
    }
    //printf("sorted 2! %d %d\n", list[0], list[1]);
    return;
  }
  
  // recursive case
  //printf("sorting n [");
  for (int i = 0; i < n; i++) {
    //printf("%d, ", list[i]);
  }
  //printf("]\n");

  int pivot = list[0];
  //printf("pivot selected: %d\n", pivot);
  
  bool sorted = true;
  int small = pivot;
  for (int i = 1; i < n; i++) {
    if (list[i] < small) {
      sorted = false;
      break;
    }
    small = list[i];
  }
  if (sorted) {
    //printf("sorted already\n");
    return;
  }
  
  int lesser_idx = -1;
  int greater_idx = n;
  while (greater_idx - lesser_idx != 1) {
    if (list[lesser_idx + 1] < pivot) {
      lesser_idx++;
    } else {
      swap(&list[lesser_idx + 1], &list[greater_idx - 1]);
      greater_idx--;
    }
  }

  //printf("separated around pivot %d n [", pivot);
  for (int i = 0; i < n; i++) {
    //printf("%d, ", list[i]);
  }
  //printf("]\n");

  if (lesser_idx > -1) {
    //printf("recursing [0,%d)\n", lesser_idx + 1);
    sort(list, lesser_idx + 1);
  }
  if (greater_idx < (n - 1)) {
    //printf("recursing [%d,%d)\n", greater_idx, n);
    sort(list + greater_idx, n - greater_idx);
  }

  //printf("sorted n [");
  for (int i = 0; i < n; i++) {
    //printf("%d, ", list[i]);
  }
  //printf("]\n");
}

static void part_1() {

  // parse from file
  int* list1;
  int* list2;
  int ll = fill_lists(&list1, &list2);

  // sort both lists
  sort(list1, ll);
  sort(list2, ll);

  // loop thru both lists and sum difference (in code)
  int total_dif = 0;
  for (int i = 0; i < ll; i++) {
    int dif = abs(list1[i] - list2[i]);
    total_dif += dif;
  }
  printf("%d\n", total_dif);

  free(list1);
  free(list2);
  list1 = list2 = NULL;
}








struct frequency_entry {
  int num;
  int freq;
};

static void part_2() {

  // parse from file
  int* list1;
  int* list2;
  int ll = fill_lists(&list1, &list2);

  // sort both lists
  sort(list1, ll);
  sort(list2, ll);

  int fl = 0;
  struct frequency_entry* fes = malloc(sizeof(struct frequency_entry) * ll);

  for (int i = 0; i < ll; i++) {
    if (fl == 0 || fes[fl - 1].num != list2[i]) {
      fes[fl].num = list2[i];
      fes[fl].freq = 1;
      fl++;
    } else {
      fes[fl - 1].freq++;
    }
  }

  int total_score = 0;
  for (int i = 0; i < ll; i++) {
    for (int j = 0; j < fl; j++) {
      if (list1[i] == fes[j].num) {
        total_score += list1[i] * fes[j].freq;
        break;
      }
    }
  }

  printf("part 2 %d\n", total_score);

  free(list1);
  free(list2);
  list1 = list2 = NULL;
}

static int sz = 9;
static int stuff[] = {5, 3, 4, 1, 6, 3, 2, 3, 8};


int main() {
  part_2();
  //sort(stuff, sz);

  return EXIT_SUCCESS;
}


