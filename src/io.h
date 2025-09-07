#ifndef IO_H
#define IO_H

#include <raylib.h>

typedef struct {
  Vector3 move;
  Vector2 mouse;
  float zoom;
} Input;

Input input_get();

#endif
