#include "../../src/arrays.c"
#include "./day3_lib.c"
#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *fptr = fopen("input.txt", "r");
  char line[140];
  char *nums = "0123456789";
  // ----------------------

  int counter = 0;
  while (fgets(line, sizeof(line), fptr) && counter < 2) {
    ++counter;
    printf("%s\n", line);

    int line_length = get_buffer_length(line, sizeof(line));

    for (int i = 0; i < line_length; ++i) {

      char curr = line[i];
      printf("%c", curr);

      checkForPart();
      if (curr == '.') {
        continue;
      }
      if (strstr(nums, &curr)) {
        printf("founda!");
      } else {
        printf("null!");
      }
    }
    printf("\n");

    // printf("%s\n", line);
  }

  // ----------------------
  fclose(fptr);
}
