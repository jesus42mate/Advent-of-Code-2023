#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#import "stdbool.h"

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



