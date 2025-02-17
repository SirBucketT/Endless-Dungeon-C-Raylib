//
// Created by theodor on 2025-02-17.
//
#include "raylib.h"
#include <stdio.h>
#include "header.h"

PlayerData player = { .position = {0, 0}, .health = 100, .damage = 10, .score = 0 };

void GameManager(void){
    char scoreText[50];
    sprintf(scoreText, "Current Score: %d", player.score);

    DrawText(scoreText, 20, 20, 20, WHITE);

    if (player.health <= 0) {
        player.health = 0;
        DrawText("Game Over", SCREEN_WIDTH/2 -150, SCREEN_HEIGHT/2, 40, RED);
    }

    //game over test code
    if (IsKeyPressed(KEY_A)) {
        player.health = 0;
    }
}

void Player(void) {

}