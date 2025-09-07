#ifndef CAMERA_H
#define CAMERA_H

#include "io.h"
#include "raylib.h"

void camera_init();
void camera_update(Input input, Vector3 screenMovement, float dt);

extern Camera3D CAMERA;

#endif
