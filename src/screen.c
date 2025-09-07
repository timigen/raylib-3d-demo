#include "io.h"
#include <raylib.h>

const float EDGE_SCROLL_ZONE = 50.0f;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;

void screen_init() {
  SCREEN_WIDTH = GetScreenWidth();
  SCREEN_HEIGHT = GetScreenHeight();
}

Vector3 screen_move(Input input) {
  Vector3 move = {0};

  // Edge scrolling
  if (input.mouse.x < EDGE_SCROLL_ZONE)
    move.x -= 1;
  if (input.mouse.x > SCREEN_WIDTH - EDGE_SCROLL_ZONE)
    move.x += 1;
  if (input.mouse.y < EDGE_SCROLL_ZONE)
    move.z -= 1;
  if (input.mouse.y > SCREEN_HEIGHT - EDGE_SCROLL_ZONE)
    move.z += 1;

  return move;
}
