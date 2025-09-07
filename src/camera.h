#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

void camera_init();
void camera_update(float dt);

extern Camera3D *CAMERA;

#endif
