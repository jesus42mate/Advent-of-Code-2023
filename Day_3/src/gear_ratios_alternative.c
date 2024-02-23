#include "../../src/arrays.c"
#include "./day3_lib.c"
#include "./engine_parts.c"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 142

void printPartValue(struct Part *part);

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
  fptr = fopen("src/input.txt", "r");
  if (fptr == NULL) {
    perror("Failed opening file.\n");
    return -1;
  }
  struct Box box = {};

  for (int lc = 0; lc < LINE_LENGTH; ++lc) {
    struct Line line;
    box.lines[lc] = line;
  }
  // ----------------------

  int line_counter = 0;
  struct Part array_of_parts[400] = {};
  while (fgets(line, sizeof(line), fptr) && line_counter < 1) {

    struct Line *current_line = &box.lines[line_counter];
    strcpy(current_line->arr, line);

    //printf("line![%d]: %s\n", line_counter, current_line->arr);

    int last_part_seen_index = 0;

    bool inPart = false;
    int part_position = 0;
    for (int i = 0; i < LINE_LENGTH; ++i) {
      char curr = current_line->arr[i];
      struct Part *lastPartSeen = &array_of_parts[last_part_seen_index];

      if (isdigit(curr) && !inPart) {
        inPart = true;
        lastPartSeen->value[part_position] = curr;
        continue;
      } 
      if (isdigit(curr) && inPart) {
        ++part_position;
        lastPartSeen->value[part_position] = curr;
        continue;
      }
      if (!isdigit(curr) && inPart) {
        inPart = false;
        part_position = 0;
        continue;
      }
      if (!isdigit(curr) && !inPart) {
        ++last_part_seen_index;
        continue;
      }
    }


    ++line_counter;
  }
  for (int com = 0; com < 400; ++com) {
    printPartValue(&array_of_parts[com]);
  }

  // ----------------------
  fclose(fptr);
}
