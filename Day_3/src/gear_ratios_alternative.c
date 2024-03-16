#include "../../src/arrays.c"
#include "./gear_ratios_lib.c"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

# define LINE_LENGTH 140

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

void setPartValue(char *buffer, char value, int pos) 
{
  if (pos == 0)
  {
    buffer[2] = value;
  }
  if (pos == 1)
  {
    buffer[1] = value;
  }
  if (pos == 2)
  {
    buffer[0] = value;
  }
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
  char box   [LINE_LENGTH][LINE_LENGTH];  // where we store all lines
  // -------------------------------------------------------------------
  int line_number = 0;
  int curr_part[3];

  while (fgets(buffer, LINE_LENGTH + 2, fptr) != NULL) 
  {
    for (int x = 0; x < LINE_LENGTH; ++x) 
      box[line_number][x] = buffer[x];

    printf("box[%d] :: %s\n", line_number, box[line_number]);
    if (line_number == 0) {
      // some tests 
      assert_eq(box[line_number][0]  , buffer[0]);
      assert_eq(box[line_number][13] , buffer[13]);
      assert_eq(box[line_number][139], buffer[139]);
      assert_eq(box[line_number][0]  , '.');
      assert_eq(box[line_number][13] , '6');
      assert_eq(box[line_number][139], '1');
    }
    ++line_number;
  }

  bool inPart = false;
  int y = 0;
  int x = 0;
  while (y < 2)
  {
    char *cur_line = box[y];
    char *top_line  = box[y - 1];
    char *bot_line  = box[y + 1];

    for (int i = LINE_LENGTH - 1; i >= 0; --i) 
    {
      x = i;
      char curr_char = cur_line[x];

      if (isdigit(curr_char)) {
        if (!inPart) {
          inPart = true;
          curr_part[0] = '0';
          curr_part[1] = '0';
          curr_part[2] = '0';
          continue;
        }
        if (inPart) {
          continue;
        }
      } 
      if (!isdigit(curr_char))
      {
        if (curr_char != '.') {
          // it's  a symbol
          char upright   = top_line[x + 1];
          char upleft    = top_line[x - 1];
          char downright = bot_line[x + 1];
          char downleft  = bot_line[x - 1];
          char left      = cur_line[x - 1];
          char right     = cur_line[x + 1];
          printf("symbol: %c\n", box[y][x]);
          if (isdigit(upright)) {  // up-right
            int part[3];
            int p1 = 0;
            int p2 = 0;
            int p3 = 0;

            if (isdigit(top_line[x + 2]) && isdigit(top_line[x + 3])) {
              p3 = top_line[x + 3];
              p2 = top_line[x + 2] * 10;
              p1 = top_line[x + 1] * 100;
            }
            if (isdigit(top_line[x + 2]) && isdigit(top_line[x])) {
              p3 = top_line[x + 2];
              p2 = top_line[x + 1] * 10;
              p1 = top_line[x    ] * 100;
            }
            if (isdigit(top_line[x - 1]) && isdigit(top_line[x])) {
              p3 = top_line[x + 1];
              p2 = top_line[x    ] * 10;
              p1 = top_line[x - 1] * 100;
            }
            // remove the digits from the box so that it can't be loaded again
          } 
          if (isdigit(box[y + 1][x - 1])) {
          }
        }
        if (!inPart) {
          continue;
        }
        if (inPart) {
          continue;
        }

      }

    }

    ++y;
  }

  // ----------------------
  fclose(fptr);
}
