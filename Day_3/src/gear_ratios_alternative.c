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
    printf("box[%d] -> %s", line_number, box[line_number]); 
    line_number++;
  }

  int part = 0;
  int total = 0;

  bool inPart = false;
  int y = 0;
  int x = 0;
  while (y < 4) {
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
        // check for right side numbers
        if (isdigit(cur_line[x + 1])) {
          part = 0;
          if (x < 138 && isdigit(cur_line[x + 2])) {
            if (x < 137 && isdigit(cur_line[x + 3])) {
              part += (cur_line[x + 3]) - '0';
              part += (cur_line[x + 2] - '0') * 10;
              part += (cur_line[x + 1] - '0') * 100;
              cur_line[x + 3] = '.';
              cur_line[x + 2] = '.';
              cur_line[x + 1] = '.';
            } else {
              part += (cur_line[x + 2] - '0');
              part += (cur_line[x + 1] - '0') * 10;
              cur_line[x + 2] = '.';
              cur_line[x + 1] = '.';
            }
          } else {
            part += ((int) cur_line[x + 1]);
            cur_line[x + 1] = '.';
          }
          printf("found: %d\n", part);
          total += part;
        }
        // check for right side numbers
        if (isdigit(cur_line[x - 1])) {
          part = 0;
          if (x > 1 && isdigit(cur_line[x - 2])) {
            if (x > 2 && isdigit(cur_line[x - 3])) {
              part += (cur_line[x - 1] - '0');
              part += (cur_line[x - 2] - '0') * 10;
              part += (cur_line[x - 3] - '0') * 100;
              cur_line[x - 1] = '.';
              cur_line[x - 2] = '.';
              cur_line[x - 3] = '.';
            } else {
              part += (cur_line[x - 1] - '0');
              part += (cur_line[x - 2] - '0') * 10;
              cur_line[x - 1] = '.';
              cur_line[x - 2] = '.';
            }
          } else {
            part += ((int) cur_line[x + 1]);
            cur_line[x + 1] = '.';
          }
          printf("found: %d\n", part);
          total += part;
        }

        if (isdigit(pre_line[x])) {
          if (isdigit(pre_line[x - 1]) && isdigit(pre_line[x + 1])) {
            part = 0;
            printf("at: (%d:%d)\n", x, y);
            part += (pre_line[x + 1] - '0');
            part += (pre_line[x    ] - '0') * 10;
            part += (pre_line[x - 1] - '0') * 100;
            pre_line[x + 1] = '.' ;
            pre_line[x]     = '.' ;
            pre_line[x - 1] = '.' ;
            printf("found: %d\n", part);
            total += part;
          }
          if (isdigit(pre_line[x - 1]) && isdigit(pre_line[x - 2])) {
            part = 0;
            part += (pre_line[x] - '0');
            part += (pre_line[x - 1] - '0') * 10;
            part += (pre_line[x - 2] - '0') * 100;
            pre_line[x]     = '.';
            pre_line[x - 1] = '.';
            pre_line[x - 2] = '.';
            printf("found: %d\n", part);
            total += part;
          }
          if (isdigit(pre_line[x + 1]) && isdigit(pre_line[x + 2])) {
            part = 0;
            part += (pre_line[x + 2] - '0');
            part += (pre_line[x + 1] - '0') * 10;
            part += (pre_line[x]     - '0') * 100;
            pre_line[x]     = '.';
            pre_line[x + 1] = '.';
            pre_line[x + 2] = '.';
            printf("found: %d\n", part);
            total += part;
          }
        }
        if (isdigit(nex_line[x])) {
          part = 0;
          if (isdigit(nex_line[x - 1]) && isdigit(nex_line[x + 1])) {
            part += (nex_line[x + 1] - '0');
            part += (nex_line[x    ] - '0') * 10;
            part += (nex_line[x - 1] - '0') * 100;
            nex_line[x + 1] = '.' ;
            nex_line[x]     = '.' ;
            nex_line[x - 1] = '.' ;
            printf("found: %d\n", part);
            total += part;
          }
          if (isdigit(nex_line[x - 1]) && isdigit(nex_line[x - 2])) {
            part += (nex_line[x] - '0');
            part += (nex_line[x - 1] - '0') * 10;
            part += (nex_line[x - 2] - '0') * 100;
            nex_line[x]     = '.';
            nex_line[x - 1] = '.';
            nex_line[x - 2] = '.';
            printf("found: %d\n", part);
            total += part;
          }
          if (isdigit(nex_line[x + 1]) && isdigit(nex_line[x + 2])) {
            part += (nex_line[x + 2] - '0');
            part += (nex_line[x + 1] - '0') * 10;
            part += (nex_line[x]     - '0') * 100;
            nex_line[x]     = '.';
            nex_line[x + 1] = '.';
            nex_line[x + 2] = '.';
            printf("found: %d\n", part);
            total += part;
          }
        }
        if (x < 136) {
          if (
            isdigit(pre_line[x + 1]) &&
            isdigit(pre_line[x + 2]) &&
            isdigit(pre_line[x + 3]))
          {
            part = 0;
            part += (pre_line[x + 3] - '0');
            part += (pre_line[x + 2] - '0') * 10;
            part += (pre_line[x + 1] - '0') * 100;
            pre_line[x + 3] = '.';
            pre_line[x + 2] = '.';
            pre_line[x + 1] = '.';
            printf("found: %d\n", part);
            total += part;
          }
          if (
            isdigit(nex_line[x + 1]) &&
            isdigit(nex_line[x + 2]) &&
            isdigit(nex_line[x + 3]))
          {
            part = 0;
            part += (nex_line[x + 3] - '0');
            part += (nex_line[x + 2] - '0') * 10;
            part += (nex_line[x + 1] - '0') * 100;
            nex_line[x + 3] = '.';
            nex_line[x + 2] = '.';
            nex_line[x + 1] = '.';
            printf("found: %d\n", part);
            total += part;
          }
        }
        if (x > 2) {
          if (
            isdigit(pre_line[x - 1]) &&
            isdigit(pre_line[x - 2]) &&
            isdigit(pre_line[x - 3]))
          {
            part = 0;
            part += (pre_line[x - 1] - '0');
            part += (pre_line[x - 2] - '0') * 10;
            part += (pre_line[x - 3] - '0') * 100;
            pre_line[x - 1] = '.';
            pre_line[x - 2] = '.';
            pre_line[x - 3] = '.';
            printf("found: %d\n", part);
            total += part;
          }
          if (
            isdigit(nex_line[x - 1]) &&
            isdigit(nex_line[x - 2]) &&
            isdigit(nex_line[x - 3]))
          {
            part = 0;
            part += (nex_line[x - 1] - '0');
            part += (nex_line[x - 2] - '0') * 10;
            part += (nex_line[x - 3] - '0') * 100;
            nex_line[x - 1] = '.';
            nex_line[x - 2] = '.';
            nex_line[x - 3] = '.';
            printf("found: %d\n", part);
            total += part;
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
