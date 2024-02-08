#include "../../src/arrays.c"
#include "./day3_lib.c"
#include "./engine_parts.c"
#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 142

struct Line {
  char arr[LINE_LENGTH];
};

struct Box {
  struct Line lines[LINE_LENGTH];
};

int main(int argc, char *argv[]) {

  char *nums = "0123456789";
  char line[LINE_LENGTH];

  FILE *fptr;
  fptr = fopen("input.txt", "r");
  if (fptr == NULL) {
    perror("Failed opening file.\n");
    return -1;
  }
  struct Box container = {};

  for (int l = 0; l < LINE_LENGTH; ++l) {
    struct Line line;
    container.lines[l] = line;
    printf("%s\n", container.lines[l].arr);
  }
  // ----------------------

  const char *one = "32";
  char *ret = strstr(nums, one);
  if (ret == NULL) {
    printf("Null!");
  } else {
    printf("%s\n", ret);
  }
  int line_counter = 0;
  while (fgets(line, sizeof(line), fptr) && line_counter < 25) {

    struct Line *current_line = &container.lines[line_counter];
    strcpy(current_line->arr, line);

    printf("line[%d]: %s\n", line_counter, current_line->arr);
    // printf("line: %s\n", line);

    for (int i = 0; i < LINE_LENGTH; ++i) {
      // TODO: FIX THE SEGMENTATION FAULT THAT HAPPENS HERE

      // char curr = current_line->arr[i];
      // char *ret = strstr(nums, &curr);
      // printf("ret: %c", *ret);

      // if (strstr(nums, &curr)) {
      //   printf("Number found!: %c\n", curr);
      // }
      // if (curr != '.' && strstr(nums, &curr) == NULL) {
      //   printf("%c is not inside nums\n", curr);
      // }
      // if (curr != '.' && strstr(nums, &curr)) {
      //   printf("Symbol found!: %c\n", curr);
      // }
    }

    ++line_counter;
  }

  // ----------------------
  fclose(fptr);
}
