#ifndef CAMERA_H
#define CAMERA_H

#include "io.h"
#include "raylib.h"

void camera_init();
void camera_update(Input input, Vector3 screenMovement, float dt);
void camera_zoom(float zoom);
void camera_screen_move(Vector3 movement);
void camera_wasd_move(Vector3 movement);
void camera_move(Vector3 movement);

extern Camera3D CAMERA;

#endif
