#include "raylib.h"

Camera3D CAMERA = {0};

const float ZOOM_SPEED = 3.0f;
const float MIN_ZOOM = 15.0f;
const float MAX_ZOOM = 80.0f;
const float EDGE_SCROLL_ZONE = 50.0f;
int screenWidth;
int screenHeight;
float cameraHeight = 25.0f;

void camera_init() {
  CAMERA.position = (Vector3){0.0f, cameraHeight, 0.0f};
  CAMERA.target = (Vector3){0.0f, 0.0f, 0.0f};
  CAMERA.up = (Vector3){0.0f, 1.0f, 0.0f};
  CAMERA.fovy = 45.0f;
  CAMERA.projection = CAMERA_PERSPECTIVE;

  screenWidth = GetScreenWidth();
  screenHeight = GetScreenHeight();
}

void camera_update(float dt) {
  CAMERA.position.x += dt * CAMERA_SPEED * GetMouseDelta().x;
  CAMERA.position.z += dt * CAMERA_SPEED * GetMouseDelta().y;
}
