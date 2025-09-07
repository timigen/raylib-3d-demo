#include "camera.h"
#include "io.h"
#include "raylib.h"
#include "raymath.h"

Camera3D CAMERA = {0};

const float moveSpeed = 15.0f;
const float CAMERA_SPEED = 3.0f;
const float ZOOM_SPEED = 3.0f;
const float MIN_ZOOM = 15.0f;
const float MAX_ZOOM = 80.0f;

float cameraHeight = 25.0f;

void camera_init() {
  CAMERA.position =
      (Vector3){0.0f, cameraHeight, cameraHeight}; // RTS side angle
  CAMERA.target = (Vector3){0.0f, 0.0f, 0.0f};
  CAMERA.up = (Vector3){0.0f, 1.0f, 0.0f};
  CAMERA.fovy = 45.0f;
  CAMERA.projection = CAMERA_PERSPECTIVE;
}

void camera_update(Input input, Vector3 screenMove, float dt) {
  // Handle zoom
  camera_zoom(input.zoom);

  Vector3 screenMovement = Vector3Scale(screenMove, moveSpeed * dt);
  camera_screen_move(screenMovement);

  Vector3 wasdMovement = Vector3Scale(input.move, moveSpeed * dt);
  camera_wasd_move(wasdMovement);
}

void camera_zoom(float zoom) {
  if (zoom != 0) {
    cameraHeight -= zoom * ZOOM_SPEED;
    if (cameraHeight < MIN_ZOOM)
      cameraHeight = MIN_ZOOM;
    if (cameraHeight > MAX_ZOOM)
      cameraHeight = MAX_ZOOM;
  }

  CAMERA.position.y = cameraHeight;
}

void camera_wasd_move(Vector3 movement) { camera_move(movement); }

void camera_screen_move(Vector3 movement) { camera_move(movement); }

void camera_move(Vector3 movement) {
  Vector3 newPos = Vector3Add(CAMERA.position, movement);
  float mapBound = 16000.0f * 0.4f; // MAP_SIZE * 0.4f
  if (newPos.x > -mapBound && newPos.x < mapBound)
    CAMERA.position.x = newPos.x;
  if (newPos.z > -mapBound && newPos.z < mapBound)
    CAMERA.position.z = newPos.z;

  // Update camera position and target for RTS perspective with side angle
  float offsetRatio = cameraHeight / 25.0f; // Scale offset with zoom
  CAMERA.target = (Vector3){CAMERA.position.x, 0.0f,
                            CAMERA.position.z - (10.0f * offsetRatio)};
}
