#include "../../src/arrays.c"
#include "./day3_lib.c"
#include "./engine_parts.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 141
#define PART_LIST_LENGTH 1204

void printPartValue(struct Part *part);

void calculateValueAndStore(int digit, int *into, int position) {
  if (position == 0) {
    *into += digit;

  } else if (position == 1) {
    *into += digit * 10;

  } else if (position == 2) {
    *into += digit * 100;

  }
}

struct Line {
  char arr[LINE_LENGTH];
};

struct Box {
  struct Line lines[LINE_LENGTH];
};

int main(int argc, char *argv[]) {

  FILE *fptr;
  fptr = fopen("src/input.txt", "r");
  if (fptr == NULL) 
  {
    perror("Failed opening file. Maybe not found?\n");
    return -1;
  }


  struct Part array_of_parts[PART_LIST_LENGTH] = {};
  struct Box box = {};

  char line[LINE_LENGTH];

  for (int position = 0; position < LINE_LENGTH; ++position) {
    struct Line line;
    box.lines[position] = line;
  }
  // ----------------------

  int line_counter = 1;
  int last_part_seen_index = 0;

  while (fgets(line, LINE_LENGTH + 1, fptr) && line_counter <= 140)
  {
    struct Line *current_line = &box.lines[line_counter];
    strcpy(current_line->arr, line);

    printf("line![%d]: %s\n", line_counter, current_line->arr);

    bool inPart = false;
    int curr_part_val = 0;
    int part_position = 0;

    for (int i = LINE_LENGTH - 1; i >= 0; --i) // traverse the line backwards for easier part retrieval
    {
      int current_char = current_line->arr[i];
      struct Part *lastPartSeen = &array_of_parts[last_part_seen_index];

      if (!isdigit(current_char) && current_char != '.') {

      }

      if (!isdigit(current_char) && !inPart) 
      {
        continue;
      }

      if (isdigit(current_char) && !inPart) 
      {
        inPart = true;
        calculateValueAndStore(current_char - '0', &curr_part_val, part_position);
        ++part_position;
        continue;
      }

      if (isdigit(current_char) && inPart) 
      {
        calculateValueAndStore(current_char - '0', &curr_part_val, part_position);
        ++part_position;
        continue;
      }

      if (!isdigit(current_char) && inPart) 
      {
        inPart = false;
        ++last_part_seen_index;

        lastPartSeen->value = curr_part_val;

        curr_part_val = 0;
        part_position = 0;

        continue;
      }
    }
    ++line_counter;

  }
  for (int com = 0; com < PART_LIST_LENGTH; ++com) {
    //printPartValue(&array_of_parts[com]);
  }

  // ----------------------
  fclose(fptr);
}
