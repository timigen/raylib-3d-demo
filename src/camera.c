#include "io.h"
#include "raylib.h"

Camera3D CAMERA = {0};

const float moveSpeed = 15.0f;
const float CAMERA_SPEED = 3.0f;
const float ZOOM_SPEED = 3.0f;
const float MIN_ZOOM = 15.0f;
const float MAX_ZOOM = 80.0f;

float cameraHeight = 25.0f;

void camera_init() {
  CAMERA.position = (Vector3){0.0f, cameraHeight, 0.0f};
  CAMERA.target = (Vector3){0.0f, 0.0f, 0.0f};
  CAMERA.up = (Vector3){0.0f, 1.0f, 0.0f};
  CAMERA.fovy = 45.0f;
  CAMERA.projection = CAMERA_PERSPECTIVE;
}

void camera_update(Input input, Vector3 screenMovement, float dt) {
  if (input.zoom != 0) {
    cameraHeight -= input.zoom * ZOOM_SPEED * dt;
    if (cameraHeight < MIN_ZOOM)
      cameraHeight = MIN_ZOOM;
    if (cameraHeight > MAX_ZOOM)
      cameraHeight = MAX_ZOOM;
  }
}
