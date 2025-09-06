#include "raylib.h"

int main(void) {
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(0, 0, "raylib template");
    const int WIDTH = GetRenderWidth();
    const int HEIGHT = GetRenderHeight();
    const int FONT_SIZE = 10;
    const int TARGET_FPS = 120;
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        DrawText(TextFormat("%d x %d", WIDTH, HEIGHT), 10, 30, FONT_SIZE, RED);
        DrawText("raylib template", 10, 40, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
