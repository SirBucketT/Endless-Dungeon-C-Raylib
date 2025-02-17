#include <stdio.h>

#include "header.h"
#include "raylib.h"

GameState currentState = MENU;

void UserInterface(Texture2D buttonTexture) {
    Rectangle buttonRect = { SCREEN_WIDTH/2 - buttonTexture.width/2, SCREEN_HEIGHT - buttonTexture.height - 50, buttonTexture.width, buttonTexture.height };

    if (currentState == MENU) {
        Vector2 mousePoint = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, buttonRect)) {
            currentState = GAME;
        }
    }

    if (currentState == MENU) {
        DrawText("Main Menu", SCREEN_WIDTH/2 - 100, 100, 40, DARKGRAY);
        DrawTexture(buttonTexture, buttonRect.x, buttonRect.y, WHITE);
    }
    else if (currentState == GAME) {
        DrawText("Game Screen", SCREEN_WIDTH/2 - 100, 100, 40, DARKGRAY);
    }
}
