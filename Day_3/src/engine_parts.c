#include <stdio.h>
#include <stdbool.h>

#define MAX_VALUE_LENGTH 10
#define LINE_LENGTH 141

struct Line {
  char arr[LINE_LENGTH];
};

struct Box {
  struct Line lines[LINE_LENGTH];
};


char *nums = "0123456789";

struct Position {
  int x;
  int y;
};

void printPosition(struct Position *pos) {
  printf("[%d, %d]\n", pos->x, pos->y);
}

struct Symbol {
  struct Position positions;
};

bool positionsAreEqual(struct Position pos, struct Position pos2) {
  if (pos.x == pos2.x &&
      pos.y == pos2.y
  ) {
    return true;
  }
  return false;
}

void checkForPartsAround(struct Symbol symbol, struct Position pos);

struct Part {
  int value;
  bool isEnginePart;
  struct Position positions[];
};

void calculateValueAndStore(int digit, int *into, int position) {
  if (position == 0) {
    *into += digit;

  } else if (position == 1) {
    *into += digit * 10;

  } else if (position == 2) {
    *into += digit * 100;

  }
}

void calculatePositionAndStore(int x, int y, struct Part *part, int value_index) {
  struct Position pos = { x, y };
  part->positions[value_index] = pos;
}

void printPartValue(struct Part *part) {
  printf("%d\n", part->value);
}

