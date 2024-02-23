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

void checkForPartsAround(struct Symbol symbol);

struct Part {
  int value[MAX_VALUE_LENGTH];
  struct Position position[];
};

void printPartValue(struct Part *part) {
  for (int i = 0; i < sizeof(part->value); ++i) {
    printf("%i", part->value[i]);
  }
  printf("\n");
}

struct EnginePart {
  int value;
};

// We don't need to calculate the value unless it is an engine part
struct EnginePart makeEnginePart(struct Part *part) {
  struct EnginePart EP;
  int value_as_int = 0;

  for (int i = 0; i < MAX_VALUE_LENGTH; ++i) {
    value_as_int += part->value[i];
  }

  EP.value = value_as_int;
  return EP;
}
