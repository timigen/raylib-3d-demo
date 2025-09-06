#ifndef ENGINE_H
#define ENGINE_H

#include "raylib.h"

void engine_init(Camera3D *camera);
void engine_run();
void engine_update(float dt);

extern Camera3D *CAMERA;

#endif
