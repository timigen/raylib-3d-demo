#include "raylib.h"
#include "raymath.h"
#include <math.h>

#define MAP_SIZE 16000.0f
#define TILE  1.0f

int main(void) {
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, "raylib 3D");
    SetTargetFPS(60);

    Camera3D cam = {0};
    cam.position = (Vector3){ 10.0f, 10.0f, 18.0f };
    cam.target   = (Vector3){  0.0f,  1.0f,  0.0f };
    cam.up       = (Vector3){  0.0f,  1.0f,  0.0f };
    cam.fovy = 60.0f;
    cam.projection = CAMERA_PERSPECTIVE;

    DisableCursor();
    float yaw = 180.0f, pitch = -20.0f;
    const float moveSpeed = 8.0f;
    const float mouseSens = 0.10f;

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
            DrawPlane((Vector3){  0.0f,  0.0f,  0.0f }, (Vector2){ MAP_SIZE, MAP_SIZE }, (Color){ 120, 120, 120, 255});
            EndMode3D();

        DrawText("WASD + mouse to move | ESC to quit", 10, 10, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
