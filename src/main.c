#include "raylib.h"
#include "raymath.h"
#include <math.h>
#define MAP_W 16
#define MAP_H 16
#define TILE  1.0f

// 0 = empty, 1 = grass, 2 = dirt, 3 = stone, 4 = water
static const int MAP[MAP_H][MAP_W] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,1},
    {1,0,3,3,0,0,0,2,2,0,0,3,3,0,0,1},
    {1,0,3,0,0,0,0,2,2,0,0,0,3,0,0,1},
    {1,0,3,0,0,4,4,4,4,4,0,0,3,0,0,1},
    {1,0,3,0,0,4,0,0,0,4,0,0,3,0,0,1},
    {1,0,3,0,0,4,0,0,0,4,0,0,3,0,0,1},
    {1,0,3,3,0,4,4,4,4,4,0,3,3,0,0,1},
    {1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,1},
    {1,0,3,3,0,0,0,2,2,0,0,3,3,0,0,1},
    {1,0,3,0,0,0,0,2,2,0,0,0,3,0,0,1},
    {1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

static Color tile_color(int t) {
    switch (t) {
        case 1: return (Color){  90, 200,  90, 255}; // grass
        case 2: return (Color){ 140, 100,  60, 255}; // dirt
        case 3: return (Color){ 120, 120, 120, 255}; // stone
        case 4: return (Color){  70, 120, 200, 255}; // water
        default: return BLANK;
    }
}

int main(void) {
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, "raylib 3D - simple block map");
    SetTargetFPS(60);

    Camera3D cam = {0};
    cam.position = (Vector3){ 10.0f, 10.0f, 18.0f };
    cam.target   = (Vector3){  8.0f,  0.5f,  8.0f };
    cam.up       = (Vector3){  0.0f,  1.0f,  0.0f };
    cam.fovy = 60.0f;
    cam.projection = CAMERA_PERSPECTIVE;

    DisableCursor();
    float yaw = 180.0f, pitch = -20.0f;
    const float moveSpeed = 8.0f;
    const float mouseSens = 0.15f;

    while (!WindowShouldClose()) {
        Vector2 md = GetMouseDelta();
        yaw   -= md.x * mouseSens;
        pitch -= md.y * mouseSens;
        if (pitch < -89) pitch = -89;
        if (pitch >  89) pitch =  89;

        // forward/right vectors from yaw/pitch
        float cy = cosf(DEG2RAD*yaw), sy = sinf(DEG2RAD*yaw);
        float cp = cosf(DEG2RAD*pitch), sp = sinf(DEG2RAD*pitch);
        Vector3 forward = (Vector3){ -sy*cp, sp, -cy*cp };
        Vector3 right   = (Vector3){ -cy,    0,   sy     };

        float dt = GetFrameTime();
        if (IsKeyDown(KEY_W)) cam.position = Vector3Add(cam.position, Vector3Scale(forward, moveSpeed*dt));
        if (IsKeyDown(KEY_S)) cam.position = Vector3Subtract(cam.position, Vector3Scale(forward, moveSpeed*dt));
        if (IsKeyDown(KEY_A)) cam.position = Vector3Add(cam.position, Vector3Scale(right,   moveSpeed*dt));
        if (IsKeyDown(KEY_D)) cam.position = Vector3Subtract(cam.position, Vector3Scale(right,   moveSpeed*dt));
        cam.target = Vector3Add(cam.position, forward);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(cam);

            DrawGrid(32, TILE);

            for (int z = 0; z < MAP_H; ++z) {
                for (int x = 0; x < MAP_W; ++x) {
                    int t = MAP[z][x];
                    if (t == 0) continue;

                    Vector3 pos = { x*TILE, 0.0f, z*TILE };
                    Color c = tile_color(t);

                    DrawCube(pos, TILE, 0.1f, TILE, c);
                }
            }
        EndMode3D();

        DrawText("WASD + mouse to move | ESC to quit", 10, 10, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
