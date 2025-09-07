#ifndef ENGINE_H
#define ENGINE_H

#include "io.h"
#include "raylib.h"

void engine_init();
void engine_run();
void engine_update(Input input, float dt);

#endif
