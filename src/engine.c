#include "raylib.h"
#include "raymath.h"

#define MAP_SIZE 16000.0f
#define TILE 1.0f
const float moveSpeed = 15.0f;

void engine_update(float dt);

void engine_init() {
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(0, 0, "raylib 3D");
  SetTargetFPS(60);
  

  // CAMERA = cam;

  // CAMERA->position = (Vector3){0.0f, 25.0f, 25.0f};
  // CAMERA->target = (Vector3){0.0f, 0.0f, 0.0f};
  // CAMERA->up = (Vector3){0.0f, 1.0f, 0.0f};
  // CAMERA->fovy = 45.0f;
  // CAMERA->projection = CAMERA_PERSPECTIVE;
}

void engine_run() {
  float dt = GetFrameTime();
  engine_update(dt);
}

void engine_update(float dt) {
  Vector2 mousePos = GetMousePosition();
  Vector3 movement = {0};

  // Edge scrolling
  if (mousePos.x < EDGE_SCROLL_ZONE)
    movement.x -= moveSpeed * dt;
  if (mousePos.x > SCREEN_WIDTH - EDGE_SCROLL_ZONE)
    movement.x += moveSpeed * dt;
  if (mousePos.y < EDGE_SCROLL_ZONE)
    movement.z -= moveSpeed * dt;
  if (mousePos.y > SCREEN_HEIGHT - EDGE_SCROLL_ZONE)
    movement.z += moveSpeed * dt;

  // WASD movement (keeping as alternative)
  if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    movement.z -= moveSpeed * dt;
  if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    movement.z += moveSpeed * dt;
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    movement.x -= moveSpeed * dt;
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    movement.x += moveSpeed * dt;

  // Mouse wheel zoom
  float wheelMove = GetMouseWheelMove();
  if (wheelMove != 0) {
    cameraHeight -= wheelMove * ZOOM_SPEED;
    if (cameraHeight < MIN_ZOOM)
      cameraHeight = MIN_ZOOM;
    if (cameraHeight > MAX_ZOOM)
      cameraHeight = MAX_ZOOM;
  }

  // Apply movement with bounds checking
  Vector3 newPos = Vector3Add(CAMERA->position, movement);
  float mapBound = MAP_SIZE * 0.4f;
  if (newPos.x > -mapBound && newPos.x < mapBound)
    CAMERA->position.x = newPos.x;
  if (newPos.z > -mapBound && newPos.z < mapBound)
    CAMERA->position.z = newPos.z;

  // Update camera position and target for RTS perspective with side angle
  CAMERA->position.y = cameraHeight;
  float offsetRatio = cameraHeight / 25.0f; // Scale offset with zoom
  CAMERA->target = (Vector3){CAMERA->position.x, 0.0f,
                             CAMERA->position.z - (10.0f * offsetRatio)};

  BeginDrawing();
  ClearBackground(BLACK);

  BeginMode3D(*CAMERA);

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
  DrawText(TextFormat("Camera Pos: (%.1f, %.1f, %.1f)", CAMERA->position.x,
                      CAMERA->position.y, CAMERA->position.z),
           10, 70, 20, WHITE);
  EndDrawing();
}
