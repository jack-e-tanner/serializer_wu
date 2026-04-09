#include <cstdio>

#include "include/serializer.h"

struct Player {
  int id;
  float x;
  float y;
  int health;
};

int main(int argc, char** argv) {
  Player p = {1, 1.0, 2.0, 3};

  Serializer serializer{};
  serializer.serialize(p);

  serializer.print_bytes();

  Player a = serializer.deserialize<Player>();

  printf("%d, %f, %f, %d\n", a.id, a.x, a.y, a.health);

  return 0;
}