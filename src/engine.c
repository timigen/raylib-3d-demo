#include "engine.h"
#include "camera.h"
#include "io.h"
#include "raylib.h"
#include "screen.h"

#define MAP_SIZE 16000.0f
#define TILE 1.0f

void engine_init() {
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(0, 0, "raylib 3D");
  SetTargetFPS(60);
  screen_init();
  camera_init();
}

void engine_run() {
  float dt = GetFrameTime();
  Input input = input_get();
  engine_update(input, dt);
}

void engine_update(Input input, float dt) {
  Vector3 screenMove = screen_move(input);

  camera_update(input, screenMove, dt);

  BeginDrawing();
  ClearBackground(BLACK);

  BeginMode3D(CAMERA);

  // Draw the ground plane
  DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){MAP_SIZE, MAP_SIZE},
            (Color){120, 120, 120, 255});

  // Add some reference cubes at different positions
  DrawCube((Vector3){0.0f, 0.5f, 0.0f}, 1.0f, 1.0f, 1.0f, RED);
  DrawCube((Vector3){10.0f, 0.5f, 0.0f}, 1.0f, 1.0f, 1.0f, GREEN);
  DrawCube((Vector3){0.0f, 0.5f, 10.0f}, 1.0f, 1.0f, 1.0f, BLUE);
  DrawCube((Vector3){-10.0f, 0.5f, 0.0f}, 1.0f, 1.0f, 1.0f, YELLOW);
  DrawCube((Vector3){0.0f, 0.5f, -10.0f}, 1.0f, 1.0f, 1.0f, PURPLE);

  // Add some larger reference objects
  DrawCube((Vector3){20.0f, 1.0f, 20.0f}, 2.0f, 2.0f, 2.0f, ORANGE);
  DrawCube((Vector3){-20.0f, 1.0f, -20.0f}, 2.0f, 2.0f, 2.0f, PINK);

  EndMode3D();

  DrawText("WASD/Arrows or mouse edge scroll to move | Mouse wheel to zoom | "
           "ESC to quit",
           10, 10, 20, WHITE);

  DrawText(TextFormat("FPS: %d", GetFPS()), 10, 40, 20, WHITE);
  DrawText(TextFormat("Camera Pos: (%.1f, %.1f, %.1f)", CAMERA.position.x,
                      CAMERA.position.y, CAMERA.position.z),
           10, 70, 20, WHITE);
  EndDrawing();
}
