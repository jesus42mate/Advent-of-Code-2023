#include "../../src/arrays.c"
#include "./day3_lib.c"
#include "./engine_parts.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PART_LIST_LENGTH 1204

void printPartValue(struct Part *part);

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
    int a = get_buffer_length(line, sizeof(line));
    printf("line length:  %d\n", a);
    struct Line *current_line = &box.lines[line_counter];
    strcpy(current_line->arr, line);

    printf("line![%d]: %s\n", line_counter, current_line->arr);

    bool inPart = false;
    int curr_part_value = 0;
    int part_index = 0;

    for (int i = LINE_LENGTH - 1; i >= 0; --i) // traversing the line backwards for easier part retrieval
    {
      int current_char = current_line->arr[i];
      struct Part *lastPartSeen = &array_of_parts[last_part_seen_index];

      if (!isdigit(current_char)) 
      {
        if (current_char == '.') 
        {
          if (!inPart) 
          {
            continue;
          }
          if (inPart)
          {
            inPart = false;
            ++last_part_seen_index;
            lastPartSeen->value = curr_part_value;
            curr_part_value = 0;
            part_index = 0;
            continue;
          }
        }
        if (current_char != '.') 
        {
          if (inPart)
          {
            inPart = false;
            ++last_part_seen_index;
            lastPartSeen->value = curr_part_value;
            curr_part_value = 0;
            part_index = 0;
          } 
          // 
          // handle symbol case
          //
          continue;
        }
      }

      if (isdigit(current_char)) 
      {
        if (!inPart)
        {
          inPart = true;
          calculateValueAndStore(current_char - '0', &curr_part_value, part_index);
          calculatePositionAndStore(i, line_counter, lastPartSeen, part_index);
          printPosition(&lastPartSeen->positions[part_index]);
          ++part_index;
          continue;
        }
        if (inPart) 
        {
          calculateValueAndStore(current_char - '0', &curr_part_value, part_index);
          calculatePositionAndStore(i, line_counter, lastPartSeen, part_index);
          printPosition(&lastPartSeen->positions[part_index]);
          ++part_index;
          continue;
        }
      }
    }
    ++line_counter;
    printf("line counter at: %d\n", line_counter);

  }
  for (int com = 0; com < PART_LIST_LENGTH; ++com) {
    //printPartValue(&array_of_parts[com]);
  }

  // ----------------------
  fclose(fptr);
}
