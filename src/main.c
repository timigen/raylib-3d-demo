#include "raylib.h"

int main(void) {
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, "raylib 3d demo");
    const int WIDTH = GetRenderWidth();
    const int HEIGHT = GetRenderHeight();
    const int FONT_SIZE = 10;
    const int TARGET_FPS = 120;
    SetTargetFPS(TARGET_FPS);

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 8.0f, 8.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(10, 1.0f);
        EndMode3D();

        DrawFPS(10, 10);
        DrawText(TextFormat("%d x %d", WIDTH, HEIGHT), 10, 30, FONT_SIZE, RED);
        DrawText("raylib 3d demo", 10, 50, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
