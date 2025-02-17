// Created by theodor on 2025-02-17.
//
#include <assert.h>

#include "header.h"
#include "raylib.h"
#include <stdio.h>
#include <assert.h>

void ScreenRender(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Endless Dungeon");
    SetTargetFPS(60);

    Texture2D buttonTexture = LoadTexture("UI/buttonBackground.png");

    //if button texture isn't found it forces a error and makes the program not run
    assert(buttonTexture.id != 0 && "Failed to load button texture");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        UserInterface(buttonTexture);

        EndDrawing();
    }

    UnloadTexture(buttonTexture);
    CloseWindow();
}