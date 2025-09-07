#ifndef ECS_H
#define ECS_H

#include "raylib.h" // for Vector3
#include <stdbool.h>
#include <stdint.h>

#ifndef ECS_MAX_ENTITIES
#define ECS_MAX_ENTITIES 1024
#endif

typedef uint32_t Entity;

// Component bit masks
enum { C_POSITION = 1u << 0, C_VELOCITY = 1u << 1, C_RENDER = 1u << 2 };

typedef struct {
  Vector3 size; // size of cube (x,y,z) in world units
  Color color;  // color to draw
  bool wire;    // draw wireframe instead of solid
} Render;

// --- Core ---
void ecs_init(void);     // zero all masks; call once at startup
Entity ecs_create(void); // returns UINT32_MAX if full
void ecs_destroy(Entity e);
bool ecs_has(Entity e, uint32_t want);

// --- Component ops ---
void ecs_add_position(Entity e, Vector3 pos);
void ecs_add_velocity(Entity e, Vector3 vel);
void ecs_remove_position(Entity e);
void ecs_remove_velocity(Entity e);
void ecs_add_render(Entity e, Render r);
void ecs_remove_render(Entity e);

Render *ecs_get_render(Entity e);
Vector3 *ecs_get_position(Entity e);
Vector3 *ecs_get_velocity(Entity e);

// --- Systems ---
void sys_move(float dt); // requires Position + Velocity
void sys_render_3d();

#endif // ECS_H
