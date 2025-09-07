
#include "io.h"
#include "raylib.h"

Input input_get() {
  float zoom = GetMouseWheelMove();
  Vector2 mouse = GetMousePosition();
  Vector3 move = {0}; // WASD movement (keeping as alternative)
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    move.z -= 1;
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    move.z += 1;
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    move.x -= 1;
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    move.x += 1;

  Input input = {
      .zoom = zoom,
      .move = move,
      .mouse = mouse,
  };

  return input;
}
