//
// Created by theodor on 2025-02-17.
//
#include "header.h"
#include "raylib.h"

void ScreenRender() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Endless Dungeon");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Welcome to the Endless Dungeon!", 100, 100, 20, RED);
        EndDrawing();
    }

    CloseWindow();
}