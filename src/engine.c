#include "engine.h"
#include "camera.h"
#include "ecs.h"
#include "io.h"
#include "raylib.h"
#include "screen.h"

#define MAP_SIZE 16000.0f
#define TILE 1.0f

void engine_init() {
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(0, 0, "raylib 3D");
  SetTargetFPS(60);
  ecs_init();
  Entity a = ecs_create();
  ecs_add_position(a, (Vector3){0, 0, 0});
  ecs_add_velocity(a, (Vector3){0, 0, 0});
  ecs_add_render(a, (Render){.size = {5, 5, 5}, .color = RED, .wire = false});
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
  sys_move(dt);
  BeginDrawing();
  ClearBackground(BLACK);

  BeginMode3D(CAMERA);

  // Draw the ground plane
  DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){MAP_SIZE, MAP_SIZE},
            (Color){120, 120, 120, 255});

  sys_render_3d();
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
