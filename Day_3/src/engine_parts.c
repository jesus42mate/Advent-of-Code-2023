#include <stdbool.h>
#include <string.h>

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
  int value;
  struct Position position;
};

struct EnginePart {
  int value;
};

struct EnginePart makeEnginePart(struct Part *part) {
  struct EnginePart EP;
  EP.value = part->value;
  return EP;
}
