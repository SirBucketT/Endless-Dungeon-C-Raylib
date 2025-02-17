// Created by theodor on 2025-02-17.
//
#include "header.h"
#include "raylib.h"
#include <stdio.h>

void ScreenRender(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Endless Dungeon");
    SetTargetFPS(60);

    Texture2D buttonTexture = LoadTexture("UI/buttonBackground.png");


    if (buttonTexture.id == 0) {
        printf("Failed to load texture!\n");
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        UserInterface(buttonTexture);

        EndDrawing();
    }

    UnloadTexture(buttonTexture);
    CloseWindow();
}