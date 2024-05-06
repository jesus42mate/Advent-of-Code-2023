#include "../../src/arrays.c"
#include "./gear_ratios_lib.c"
#include <ctype.h>
#include <string.h>

# define LINE_LENGTH 140

bool is_long_enough_for_plus_three(int x);

void lookLeft(char *line[], int x) {
  printf("passed: %s\n", line[x - 1]);
}

bool assert_eq(char this, char that)
{
  if (this == that) 
  {
    printf("yep!\n");
    return true;
  }
  printf("not equal!\n");
  return false;
}

int main(int argc, char *argv[]) 
{
  FILE *fptr;
  fptr = fopen("src/input.txt", "r");
  if (fptr == NULL) 
  {
    perror("Failed opening file. Maybe not found?\n");
    return -1;
  }
  char buffer[LINE_LENGTH];               // where the line read goes
  char box   [LINE_LENGTH + 1][LINE_LENGTH];  // where we store all lines

  // -------------------------------------------------------------------

  int line_number = 0;
  int curr_part[3];

  // populate the box
  while (fgets(buffer, LINE_LENGTH + 2, fptr) != NULL) {
    strcpy(box[line_number], buffer);
    if (line_number < 4) 
      printf("box[%d] -> %s", line_number, box[line_number]); 
    line_number++;
  }

  int part = 0;
  int total = 0;

  bool inPart = false;
  int y = 0;
  int x = 0;
  while (y < 140) {
    char *cur_line = box[y];
    char *pre_line;
    char *nex_line;

    if (y > 0) pre_line = box[y - 1];
    else pre_line = NULL;

    if (y < 139) nex_line = box[y + 1];
    else nex_line = NULL;

    for (int i = LINE_LENGTH - 1; i >= 0; --i) {
      x = i;
      char curr_char = cur_line[x];

      if (its_symbol(curr_char)) {
        // BASIC x to x + 3 PREV
        if (isdigit(pre_line[x]) && isdigit(pre_line[x + 1]) && isdigit(pre_line[x + 2])) {
          part += (pre_line[x + 2] - '0') * 1;
          part += (pre_line[x + 1] - '0') * 10;
          part += (pre_line[x    ] - '0') * 100;
          pre_line[x    ] = '.';
          pre_line[x + 1] = '.';
          pre_line[x + 2] = '.';
          sum_total_and_cleanup(&part, &total);
        }
        // BASIC x to x - 3 PREV
        if (isdigit(pre_line[x]) && isdigit(pre_line[x - 1]) && isdigit(pre_line[x - 2])) {
          part += (pre_line[x    ] - '0') * 1;
          part += (pre_line[x - 1] - '0') * 10;
          part += (pre_line[x - 2] - '0') * 100;
          pre_line[x    ] = '.';
          pre_line[x - 1] = '.';
          pre_line[x - 2] = '.';
          sum_total_and_cleanup(&part, &total);
        }
        // BASIC x to x + 3 NEXT
        if (isdigit(nex_line[x]) && isdigit(nex_line[x + 1]) && isdigit(nex_line[x + 2])) {
          part += (nex_line[x + 2] - '0') * 1;
          part += (nex_line[x + 1] - '0') * 10;
          part += (nex_line[x    ] - '0') * 100;
          nex_line[x    ] = '.';
          nex_line[x + 1] = '.';
          nex_line[x + 2] = '.';
          sum_total_and_cleanup(&part, &total);
        }
        // BASIC x to x - 3 NEXT
        if (isdigit(nex_line[x]) && isdigit(nex_line[x - 1]) && isdigit(nex_line[x - 2])) {
          part += (nex_line[x    ] - '0') * 1;
          part += (nex_line[x - 1] - '0') * 10;
          part += (nex_line[x - 2] - '0') * 100;
          nex_line[x    ] = '.';
          nex_line[x - 1] = '.';
          nex_line[x - 2] = '.';
          sum_total_and_cleanup(&part, &total);
        }
        // BASIC THREE PREVIOUS LINE
        if (isdigit(pre_line[x])) {
          if (isdigit(pre_line[x + 1]) && isdigit(pre_line[x - 1])) {
            part += (pre_line[x + 1] - '0') * 1;
            part += (pre_line[x    ] - '0') * 10;
            part += (pre_line[x - 1] - '0') * 100;
            pre_line[x + 1] = '.';
            pre_line[x    ] = '.';
            pre_line[x - 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
        }
        // BASIC THREE NEXT LINE
        if (isdigit(nex_line[x])) {
          if (isdigit(nex_line[x + 1]) && isdigit(nex_line[x - 1])) {
            part += (nex_line[x + 1] - '0') * 1;
            part += (nex_line[x    ] - '0') * 10;
            part += (nex_line[x - 1] - '0') * 100;
            nex_line[x + 1] = '.';
            nex_line[x    ] = '.';
            nex_line[x - 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
        }
        // BASIC CASES -1 AND -2 ONLY
        if (
          isdigit(pre_line[x]) &&
          isdigit(pre_line[x - 1]) && 
          !isdigit(pre_line[x - 2])
        ) {
          part += (pre_line[x] - '0') * 1;
          part += (pre_line[x - 1] - '0') * 10;
          pre_line[x] = '.';
          pre_line[x - 1] = '.';
          sum_total_and_cleanup(&part, &total);

        }
        if (
          isdigit(nex_line[x]) &&
          isdigit(nex_line[x - 1]) && 
          !isdigit(nex_line[x - 2])
        ) {
          part += (nex_line[x] - '0') * 1;
          part += (nex_line[x - 1] - '0') * 10;
          nex_line[x] = '.';
          nex_line[x - 1] = '.';
          sum_total_and_cleanup(&part, &total);
        }
        // BASIC CASES +1 AND +2 ONLY
        if (
          isdigit(pre_line[x]) &&
          isdigit(pre_line[x + 1]) && 
          !isdigit(pre_line[x + 2])
        ) {
          part += (pre_line[x] - '0') * 1;
          part += (pre_line[x + 1] - '0') * 10;
          pre_line[x] = '.';
          pre_line[x + 1] = '.';
          sum_total_and_cleanup(&part, &total);

        }
        if (
          isdigit(nex_line[x]) &&
          isdigit(nex_line[x + 1]) && 
          !isdigit(nex_line[x + 2])
        ) {
          part += (nex_line[x] - '0') * 1;
          part += (nex_line[x + 1] - '0') * 10;
          nex_line[x] = '.';
          nex_line[x + 1] = '.';
          sum_total_and_cleanup(&part, &total);
        }

        // PREV LINE +1 +2 AND +3
        if (isdigit(pre_line[x + 1])) {
          if (x < 138 && isdigit(pre_line[x + 2])) {
            if (x < 137 && isdigit(pre_line[x + 3])) {
              part += (pre_line[x + 3] - '0') * 1;
              part += (pre_line[x + 2] - '0') * 10;
              part += (pre_line[x + 1] - '0') * 100;
              cur_line[x + 3] = '.';
              cur_line[x + 2] = '.';
              cur_line[x + 1] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (pre_line[x + 2] - '0') * 1;
              part += (pre_line[x + 1] - '0') * 10;
              cur_line[x + 2] = '.';
              cur_line[x + 1] = '.';
              sum_total_and_cleanup(&part, &total);
            }
          } else {
            part += (pre_line[x + 1] - '0');
            pre_line[x + 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
        }
        // MIDDLE LINE +1 +2 AND +3
        if (isdigit(cur_line[x + 1])) {
          if (x < 138 && isdigit(cur_line[x + 2])) {
            if (x < 137 && isdigit(cur_line[x + 3])) {
              part += (cur_line[x + 3] - '0') * 1;
              part += (cur_line[x + 2] - '0') * 10;
              part += (cur_line[x + 1] - '0') * 100;
              cur_line[x + 3] = '.';
              cur_line[x + 2] = '.';
              cur_line[x + 1] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (cur_line[x + 2] - '0');
              part += (cur_line[x + 1] - '0') * 10;
              cur_line[x + 2] = '.';
              cur_line[x + 1] = '.';
              sum_total_and_cleanup(&part, &total);
            }
          } else {
            part += cur_line[x + 1] - '0';
            cur_line[x + 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
          printf("found: %d\n", part);
          total += part;
        }

        // NEXT LINE +1 +2 AND +3
        if (isdigit(nex_line[x + 1])) {
          if (x < 138 && isdigit(nex_line[x + 2])) {
            if (x < 137 && isdigit(nex_line[x + 3])) {
              part += (nex_line[x + 3] - '0') * 1;
              part += (nex_line[x + 2] - '0') * 10;
              part += (nex_line[x + 1] - '0') * 100;
              cur_line[x + 3] = '.';
              cur_line[x + 2] = '.';
              cur_line[x + 1] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (nex_line[x + 2] - '0') * 1;
              part += (nex_line[x + 1] - '0') * 10;
              cur_line[x + 2] = '.';
              cur_line[x + 1] = '.';
              sum_total_and_cleanup(&part, &total);
            }
          } else {
            part += (nex_line[x + 1] - '0');
            nex_line[x + 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
        }

        // PREV LINE -1 -2 AND -3
        if (isdigit(pre_line[x - 1])) {
          if (x > 1 && isdigit(pre_line[x - 2])) {
            if (x > 2 && isdigit(pre_line[x - 3])) {
              part += (pre_line[x - 1] - '0') * 1;
              part += (pre_line[x - 2] - '0') * 10;
              part += (pre_line[x - 3] - '0') * 100;
              pre_line[x - 1] = '.';
              pre_line[x - 2] = '.';
              pre_line[x - 3] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (pre_line[x - 1] - '0') * 1;
              part += (pre_line[x - 2] - '0') * 10;
              pre_line[x - 1] = '.';
              pre_line[x - 2] = '.';
              sum_total_and_cleanup(&part, &total);
            }
          } else {
            part += (pre_line[x - 1] - '0');
            pre_line[x - 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
        }

        // MIDDLE LINE -1 -2 AND -3
        if (isdigit(cur_line[x - 1])) {
          if (x > 1 && isdigit(cur_line[x - 2])) {
            if (x > 2 && isdigit(cur_line[x - 3])) {
              part += (cur_line[x - 1] - '0') * 1;
              part += (cur_line[x - 2] - '0') * 10;
              part += (cur_line[x - 3] - '0') * 100;
              cur_line[x - 1] = '.';
              cur_line[x - 2] = '.';
              cur_line[x - 3] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (cur_line[x - 1] - '0');
              part += (cur_line[x - 2] - '0') * 10;
              cur_line[x - 1] = '.';
              cur_line[x - 2] = '.';
              sum_total_and_cleanup(&part, &total);
            }
          } else {
            part += cur_line[x - 1] - '0';
            cur_line[x - 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
          printf("found: %d\n", part);
          total += part;
        }
        
        // NEXT LINE -1 -2 AND -3
        if (isdigit(nex_line[x - 1])) {
          if (x < 138 && isdigit(nex_line[x - 2])) {
            if (x < 137 && isdigit(nex_line[x - 3])) {
              part += (nex_line[x - 1] - '0') * 1;
              part += (nex_line[x - 2] - '0') * 10;
              part += (nex_line[x - 3] - '0') * 100;
              cur_line[x - 1] = '.';
              cur_line[x - 2] = '.';
              cur_line[x - 3] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (nex_line[x - 1] - '0') * 1;
              part += (nex_line[x - 2] - '0') * 10;
              cur_line[x - 1] = '.';
              cur_line[x - 2] = '.';
              sum_total_and_cleanup(&part, &total);
            }
          } else {
            part += (nex_line[x - 1] - '0');
            nex_line[x - 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
        }
      }
    }
    ++y;
  }

  // ----------------------
  fclose(fptr);
}

bool is_long_enough_for_plus_three(int x) {
  return x <= 136 && x >= 3;
}

//  ...............
//  ...&...........
//  ..........%....
//  ...............
//  ...............
//  ............%..
//  ...............
