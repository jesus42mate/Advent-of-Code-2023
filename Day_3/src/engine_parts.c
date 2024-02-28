#include <stdio.h>
#include <stdbool.h>

#define MAX_VALUE_LENGTH 10

char *nums = "0123456789";

struct Position {
  int x;
  int y;
};

struct Symbol {
  struct Position position;
};

void checkForPartsAround(struct Symbol symbol, struct Position pos);

struct Part {
  int value;
  struct Position position[];
};

struct Part setPartPosition(int x, int y, int idx, struct Part *part) {
  part->position[idx].x = x;
  part->position[idx].y = y;

  return *part;
}

struct Part setPartValue(int val, struct Part *part) {
  part->value = val;
  return *part;
}

void printAllPartsFound(struct Part part[], size_t part_list_length) {
  for (int i = 0; i < part_list_length; ++i) {
  }
}

void printPartValue(struct Part *part) {
  printf("%d\n", part->value);
}

struct EnginePart {
  int value;
};

// We don't need to calculate the value unless it is an engine part
struct EnginePart makeEnginePart(struct Part *part) {
  struct EnginePart EP;
  int value_as_int = 0;

  for (int i = 0; i < MAX_VALUE_LENGTH; ++i) {
    value_as_int += part->value;
  }

  EP.value = value_as_int;
  return EP;
}
