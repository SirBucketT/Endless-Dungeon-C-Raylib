#include <stdio.h>

#include "header.h"
#include "raylib.h"

GameState currentState = MENU;


void UserInterface(Texture2D buttonTexture) {
    int buttonWidth = 300;
    int buttonHeight = 80;

    Rectangle PlayGameButton = {
        (SCREEN_WIDTH - buttonWidth) / 2,
        (SCREEN_HEIGHT - buttonHeight) / 2,
        buttonWidth,
        buttonHeight
    };

    Rectangle QuitGameButton = {
        (SCREEN_WIDTH - buttonWidth) / 2,
        PlayGameButton.y + buttonHeight + 20,
        buttonWidth,
        buttonHeight
    };

    Vector2 mousePoint = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, PlayGameButton)) {
        currentState = GAME;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePoint, QuitGameButton)) {
        currentState = QUIT_GAME;
    }


    if (currentState == MENU) {
        DrawText("Main Menu", SCREEN_WIDTH/2 - 100, 100, 40, DARKGRAY);

        //draw play game button

        Rectangle sourceRect = { 0, 0, buttonTexture.width, buttonTexture.height };
        DrawTexturePro(buttonTexture, sourceRect, PlayGameButton, (Vector2){0, 0}, 0, WHITE);

        const char *playGameText = "Play Game";
        int fontSize = 40;
        int textWidth = MeasureText(playGameText, fontSize);

        Vector2 PlayGameTextPos = {
            PlayGameButton.x + (PlayGameButton.width - textWidth) / 2,
            PlayGameButton.y + (PlayGameButton.height - fontSize) / 2
        };

        DrawText(playGameText, PlayGameTextPos.x, PlayGameTextPos.y, fontSize, WHITE);

        //draw and render quit game button

        DrawTexturePro(buttonTexture, sourceRect, QuitGameButton, (Vector2){0, 0}, 0, WHITE);
        const char *quitGameText = "Quit Game";
        int quitTextWidth = MeasureText(quitGameText, 40);
        Vector2 QuitGameTextPos = {
            QuitGameButton.x + (QuitGameButton.width - quitTextWidth) / 2,
            QuitGameButton.y + (QuitGameButton.height - 40) / 2
        };
        DrawText(quitGameText, QuitGameTextPos.x, QuitGameTextPos.y, 40, WHITE);

    }
    else if (currentState == GAME) {
        UnloadTexture(buttonTexture);
        GameManager();
    }
    else if (currentState == QUIT_GAME) {
        CloseWindow();
    }
}
