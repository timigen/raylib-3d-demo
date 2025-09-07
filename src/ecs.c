#include "ecs.h"
#include <stdio.h>

static uint32_t e_cmask[ECS_MAX_ENTITIES];
static Vector3 e_pos[ECS_MAX_ENTITIES];
static Vector3 e_vel[ECS_MAX_ENTITIES];
static Render e_render[ECS_MAX_ENTITIES];

static inline bool valid(Entity e) { return e < ECS_MAX_ENTITIES; }

void ecs_init(void) {
  for (Entity e = 0; e < ECS_MAX_ENTITIES; ++e)
    e_cmask[e] = 0;
}

Entity ecs_create(void) {
  for (Entity e = 0; e < ECS_MAX_ENTITIES; ++e) {
    if (e_cmask[e] == 0)
      return e;
  }
  return UINT32_MAX; // pool full
}

void ecs_destroy(Entity e) {
  if (!valid(e))
    return;
  e_cmask[e] = 0; // mark slot free; data left untouched
}

bool ecs_has(Entity e, uint32_t want) {
  return valid(e) && (e_cmask[e] & want) == want;
}

void ecs_add_position(Entity e, Vector3 pos) {
  if (!valid(e))
    return;
  e_pos[e] = pos;
  e_cmask[e] |= C_POSITION;
}

void ecs_add_velocity(Entity e, Vector3 vel) {
  if (!valid(e))
    return;
  e_vel[e] = vel;
  e_cmask[e] |= C_VELOCITY;
}

void ecs_remove_position(Entity e) {
  if (!valid(e))
    return;
  e_cmask[e] &= ~C_POSITION;
}

void ecs_remove_velocity(Entity e) {
  if (!valid(e))
    return;
  e_cmask[e] &= ~C_VELOCITY;
}

Vector3 *ecs_get_position(Entity e) {
  return (valid(e) && (e_cmask[e] & C_POSITION)) ? &e_pos[e] : NULL;
}

Vector3 *ecs_get_velocity(Entity e) {
  return (valid(e) && (e_cmask[e] & C_VELOCITY)) ? &e_vel[e] : NULL;
}

void ecs_add_render(Entity e, Render r) {
  if (!valid(e))
    return;
  e_render[e] = r;
  e_cmask[e] |= C_RENDER;
}

void ecs_remove_render(Entity e) {
  if (!valid(e))
    return;
  e_cmask[e] &= ~C_RENDER;
}

Render *ecs_get_render(Entity e) {
  return (valid(e) && (e_cmask[e] & C_RENDER)) ? &e_render[e] : NULL;
}

void sys_move(float dt) {
  for (Entity e = 0; e < ECS_MAX_ENTITIES; ++e) {
    uint32_t m = e_cmask[e];
    if ((m & (C_POSITION | C_VELOCITY)) == (C_POSITION | C_VELOCITY)) {
      e_pos[e].x += e_vel[e].x * dt;
      e_pos[e].y += e_vel[e].y * dt;
      e_pos[e].z += e_vel[e].z * dt;
    }
  }
}

void sys_render_3d() {
  for (Entity e = 0; e < ECS_MAX_ENTITIES; ++e) {
    if ((e_cmask[e] & (C_POSITION | C_RENDER)) == (C_POSITION | C_RENDER)) {
      Vector3 p = e_pos[e];
      Render r = e_render[e];
      if (r.wire) {
        DrawCubeWiresV(p, r.size, r.color);
      } else {
        DrawCubeV(p, r.size, r.color);
      }
    }
  }
}
