#include "../../src/arrays.c"
#include "./gear_ratios_lib.c"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

# define LINE_LENGTH 140
# define NEWLINE_AND_STRING_END 2

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

int main(int argc, char *argv[]) {
  printf("\n\n");
  FILE *fptr;
  fptr = fopen("src/input.txt", "r");
  if (fptr == NULL) 
  {
    perror("Failed opening file. Maybe not found?\n");
    return -1;
  }
  char buffer[LINE_LENGTH + 2];             // where the current line read goes
  struct Box box = { {}, LINE_LENGTH };             // where we store all lines
  //
  populate_box(&box);


  int line_number = 0;
  // populate the line_box
  printf("While loop?\n\n\n");
  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
    if (line_number > 139) {
      break;
    } else {
      for (int i = 0; i < 140; i++) {
        box.lines[line_number].data[i] = buffer[i];
      }
    }
    line_number++;
  }

  printf("\n-- 1: \n");
  print_box(&box, 140);

  int part = 0;
  int total = 0;

  int y = 0;
  while (y < 140) {
    // set current lines
    char *cur_line = box.lines[y].data;
    char *pre_line = y > 0 ? box.lines[y - 1].data : NULL;
    char *nex_line = y < 139 ? box.lines[y + 1].data : NULL;


    // traverse each line 
    for (int x = 0; x < 140; x++) {
       
      // Look for symbols
      // Add them to the total
      if (its_symbol(cur_line[x])) {
        cur_line[x] = 'n';
        
        //
        if (isdigit(pre_line[x])) {
          // BASIC THREE PREV LINE
          if (isdigit(pre_line[x + 1]) && isdigit(pre_line[x - 1])) {
            part += (pre_line[x + 1] - '0') * 1;
            part += (pre_line[x + 0] - '0') * 10;
            part += (pre_line[x - 1] - '0') * 100;
            pre_line[x + 1] = '.';
            pre_line[x + 0] = '.';
            pre_line[x - 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
          // PREV x, x - 1, x - 2
          if (isdigit(pre_line[x - 1]) && isdigit(pre_line[x - 2])) {
            part += (pre_line[x - 2] - '0') * 100;
            part += (pre_line[x - 1] - '0') * 10;
            part += (pre_line[x - 0] - '0') * 1;
            pre_line[x - 1] = '.'; 
            pre_line[x - 0] = '.'; 
            pre_line[x - 2] = '.'; 
            sum_total_and_cleanup(&part, &total);
          }
          // PREV x, x + 1, x + 2
          if (isdigit(pre_line[x + 1]) && isdigit(pre_line[x + 2])) {
            part += (pre_line[x + 2] - '0') * 1;
            part += (pre_line[x + 1] - '0') * 10;
            part += (pre_line[x + 0] - '0') * 100;
            pre_line[x + 1] = '.'; 
            pre_line[x + 0] = '.'; 
            pre_line[x + 2] = '.'; 
            sum_total_and_cleanup(&part, &total);
          }
          if (isdigit(pre_line[x + 1])) {
            part += (pre_line[x + 1] - '0') * 1;
            part += (pre_line[x + 0] - '0') * 10;
            pre_line[x + 1] = '.'; 
            pre_line[x + 0] = '.'; 
            sum_total_and_cleanup(&part, &total);
          }
          if (isdigit(pre_line[x - 1])) {
            part += (pre_line[x - 1] - '0') * 10;
            part += (pre_line[x + 0] - '0') * 1;
            pre_line[x - 1] = '.'; 
            pre_line[x + 0] = '.'; 
            sum_total_and_cleanup(&part, &total);
          }
        }

        // 
        if (isdigit(nex_line[x])) {
          // BASIC THREE NEXT LINE
          if (isdigit(nex_line[x + 1]) && isdigit(nex_line[x - 1])) {
            part += (nex_line[x + 1] - '0') * 1;
            part += (nex_line[x + 0] - '0') * 10;
            part += (nex_line[x - 1] - '0') * 100;
            nex_line[x + 1] = '.';
            nex_line[x + 0] = '.';
            nex_line[x - 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }  
          // NEXT x, x - 1, x - 2
          if (isdigit(nex_line[x - 1]) && isdigit(nex_line[x - 2])) {
            part += (nex_line[x - 2] - '0') * 100;
            part += (nex_line[x - 1] - '0') * 10;
            part += (nex_line[x - 0] - '0') * 1;
            nex_line[x - 1] = '.'; 
            nex_line[x - 0] = '.'; 
            nex_line[x - 2] = '.'; 
            sum_total_and_cleanup(&part, &total);
          }
          // NEXT x, x + 1, x + 2
          if (isdigit(nex_line[x + 1]) && isdigit(nex_line[x + 2])) {
            part += (nex_line[x + 2] - '0') * 1;
            part += (nex_line[x + 1] - '0') * 10;
            part += (nex_line[x + 0] - '0') * 100;
            nex_line[x + 1] = '.'; 
            nex_line[x + 0] = '.'; 
            nex_line[x + 2] = '.'; 
            sum_total_and_cleanup(&part, &total);
          }
          if (isdigit(nex_line[x + 1])) {
            part += (nex_line[x + 1] - '0') * 1;
            part += (nex_line[x + 0] - '0') * 10;
            nex_line[x + 1] = '.'; 
            nex_line[x + 0] = '.'; 
            sum_total_and_cleanup(&part, &total);
          }
          if (isdigit(nex_line[x - 1])) {
            part += (nex_line[x - 1] - '0') * 10;
            part += (nex_line[x + 0] - '0') * 1;
            nex_line[x - 1] = '.'; 
            nex_line[x + 0] = '.'; 
            sum_total_and_cleanup(&part, &total);
          }
        }
        //
        // PREV LINE +1 +2 AND +3
        if (isdigit(pre_line[x + 1]) && !isdigit(pre_line[x])) {
          if (x < 138 && isdigit(pre_line[x + 2])) {
            if (x < 137 && isdigit(pre_line[x + 3])) {
              part += (pre_line[x + 3] - '0') * 1;
              part += (pre_line[x + 2] - '0') * 10;
              part += (pre_line[x + 1] - '0') * 100;
              pre_line[x + 3] = '.';
              pre_line[x + 2] = '.';
              pre_line[x + 1] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (pre_line[x + 2] - '0') * 1;
              part += (pre_line[x + 1] - '0') * 10;
              pre_line[x + 2] = '.';
              pre_line[x + 1] = '.';
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
          total += part;
        }
        // NEXT LINE +1 +2 AND +3
        if (isdigit(nex_line[x + 1]) && !isdigit(nex_line[x])) {
          if (x < 138 && isdigit(nex_line[x + 2])) {
            if (x < 137 && isdigit(nex_line[x + 3])) {
              part += (nex_line[x + 3] - '0') * 1;
              part += (nex_line[x + 2] - '0') * 10;
              part += (nex_line[x + 1] - '0') * 100;
              nex_line[x + 3] = '.';
              nex_line[x + 2] = '.';
              nex_line[x + 1] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (nex_line[x + 2] - '0') * 1;
              part += (nex_line[x + 1] - '0') * 10;
              nex_line[x + 2] = '.';
              nex_line[x + 1] = '.';
              sum_total_and_cleanup(&part, &total);
            }
          } else {
            part += (nex_line[x + 1] - '0');
            nex_line[x + 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
        }

        //
        // PREV LINE -1 -2 AND -3
        if (isdigit(pre_line[x - 1]) && !isdigit(pre_line[x])) {
          if (x > 1 && isdigit(pre_line[x - 2])) {
            if (x > 2 && isdigit(pre_line[x - 3])) {
              part += (pre_line[x - 3] - '0') * 1;
              part += (pre_line[x - 2] - '0') * 10;
              part += (pre_line[x - 1] - '0') * 100;
              pre_line[x - 3] = '.';
              pre_line[x - 2] = '.';
              pre_line[x - 1] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (pre_line[x - 2] - '0') * 1;
              part += (pre_line[x - 1] - '0') * 10;
              pre_line[x - 2] = '.';
              pre_line[x - 1] = '.';
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
              part += (cur_line[x - 3] - '0') * 100;
              part += (cur_line[x - 2] - '0') * 10;
              part += (cur_line[x - 1] - '0') * 1;
              cur_line[x - 3] = '.';
              cur_line[x - 2] = '.';
              cur_line[x - 1] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (cur_line[x - 2] - '0') * 10;
              part += (cur_line[x - 1] - '0');
              cur_line[x - 2] = '.';
              cur_line[x - 1] = '.';
              sum_total_and_cleanup(&part, &total);
            }
          } else {
            part += cur_line[x - 1] - '0';
            cur_line[x - 1] = '.';
            sum_total_and_cleanup(&part, &total);
          }
          total += part;
        }
        // NEXT LINE -1 -2 AND -3
        if (isdigit(nex_line[x - 1]) && !isdigit(nex_line[x])) {
          if (x > 1 && isdigit(nex_line[x - 2])) {
            if (x > 2 && isdigit(nex_line[x - 3])) {
              part += (nex_line[x - 3] - '0') * 100;
              part += (nex_line[x - 2] - '0') * 10;
              part += (nex_line[x - 1] - '0') * 1;
              nex_line[x - 3] = '.';
              nex_line[x - 2] = '.';
              nex_line[x - 1] = '.';
              sum_total_and_cleanup(&part, &total);
            } else {
              part += (nex_line[x - 2] - '0') * 10;
              part += (nex_line[x - 1] - '0') * 1;
              nex_line[x - 2] = '.';
              nex_line[x - 1] = '.';
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
    printf("\n-- 2: \n");
    print_box(&box, 140);


    printf("Finished\n");
    printf("total -> %d\n", total); 
    // ----------------------
    fclose(fptr);
  }

bool is_long_enough_for_plus_three(int x) {
  return x <= 136 && x >= 3;
}

//  ...............
//  ..&&...........
//  ..........%....
//  ...............
//  ...............
//  ............%..
//  ...............
