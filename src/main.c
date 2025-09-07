#include "engine.h"
#include "raylib.h"

#define MAP_SIZE 16000.0f
#define TILE 1.0f

int main(void) {
  engine_init();

  while (!WindowShouldClose()) {
    engine_run();
  }

  CloseWindow();
  return 0;
}
