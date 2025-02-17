#include "header.h"
#include "raylib.h"

void UserInterface(void) {
    Texture2D buttonTexture = LoadTexture("UI/buttonBackground");
    Rectangle buttonRect = { SCREEN_WIDTH/2 - buttonTexture.width/2, SCREEN_HEIGHT, buttonTexture.width, buttonTexture.height };

    GameState currentState = MENU;
}