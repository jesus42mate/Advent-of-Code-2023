#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#import "stdbool.h"

void sum_total_and_cleanup(int *part, int *total) {
  //printf("part: %d + %d = %d\n", *part, *total, *total + *part);
  *total += *part;
  *part = 0;
}

struct Line {
  char data[140];
};

struct Box {
  struct Line lines[140];
  int len;
};


struct Line create_line() {
  struct Line line = {};
  for (int k = 0; k < 140; k++) {
    line.data[k] = '.';
  }
  return line;
}

void print_line(struct Line *line, size_t line_size, int line_number) {
  printf("\t");
  for (int i = 0; i < line_size; i++) {
    printf("%c", line->data[i]);
  }
  printf("\n");
}

void populate_box(struct Box *box) {
  for (int i = 0; i < 140; i++) {
    box->lines[i] = create_line();
  }
}

void print_box(struct Box* box, int row_range) {
  if (row_range > box->len) return;
  for (int line_number = 0; line_number < row_range; line_number++) {
    struct Line* curr_line = &box->lines[line_number];
    print_line(curr_line, sizeof(curr_line->data), line_number);

    for (int index = 0; index < 140; index++) {
    }
  }
}

bool its_symbol(char character) {
  if (!isdigit(character) && character != '.') {
    return true;
  }
  return false;
}

bool check_basic(int x, char *line) {
  if (!isdigit(line[x + 1]) && !isdigit(line[x - 1])) {

  }

}

int check_right(int x, char *line) {
  if (isdigit(line[x + 1])) {
    int part = 0;
    if (isdigit(line[x + 2]) && isdigit(line[x])) {
      part += (line[x + 2] - '0');
      part += (line[x + 1] - '0') * 10;
      part += (line[x - 0] - '0') * 100;
      return part;
    }
    if (isdigit(line[x - 1]) && isdigit(line[x])) {
      part += line[x + 1] + line[x] * 10 + line[x - 1] * 100;
      return part;
    }

    if (!(x < 137)) return NULL;

    if (isdigit(line[x + 2]) && isdigit(line[x + 3])) {
      part += (line[x + 3] - '0');
      part += (line[x + 2] - '0') * 10;
      part += (line[x + 1] - '0') * 100;
      return part;
       
    }
  }
}
//struct Part {
//  bool isEnginePart;
//  int value;
//};

typedef struct {
  bool isEnginePart;
  int value;
} Part;



