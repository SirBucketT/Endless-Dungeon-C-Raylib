//
// Created by theodor on 2025-02-17.
//
#include "raylib.h"
#include <stdio.h>
#include "header.h"

PlayerData player = { .position = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, .health = 100, .damage = 10, .score = 0 };
bool isAlive = true;

void GameManager(void){
    char scoreText[500];
    sprintf(scoreText, "Current Score: %d", player.score);

    DrawText(scoreText, 20, 20, 20, WHITE);
    Player();
}

void Player(void) {
    player.movementSpeed = 20;
    if (isAlive == true) {

        //player Character rendering
        player.SizeX = 10;
        player.SizeY = 10;
        DrawRectangle(player.position.x, player.position.y, player.SizeX, player.SizeY, WHITE);

        //score tester
        if (IsKeyPressed(KEY_K)) {
            player.score+= 10;
        }

        //game over test code
        if (IsKeyPressed(KEY_I)) {
            player.health = 0;
        }
        //------------------------------------------------------------
        //      Player movement:
        //------------------------------------------------------------
        if (IsKeyPressed(KEY_D)) {
            player.position.x += player.movementSpeed;
        } else if (IsKeyPressed(KEY_A)) {
            player.position.x -= player.movementSpeed;
        } else if (IsKeyPressed(KEY_W)) {
            player.position.y -= player.movementSpeed;
        } else if (IsKeyPressed(KEY_S)) {
            player.position.y += player.movementSpeed;
        }

    }
    if (player.health <= 0) {
        isAlive = false;
        player.health = 0;
        DrawText("Game Over", SCREEN_WIDTH/2 -150, SCREEN_HEIGHT/2, 40, RED);
    }
}