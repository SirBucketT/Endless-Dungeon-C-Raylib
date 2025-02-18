//
// Created by theodor on 2025-02-17.
//
#include "raylib.h"
#include <stdio.h>
#include "header.h"

PlayerData player = {
    .position = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2},
    .health = 100, .damage = 10, .score = 0,
    .SizeX = 10,.SizeY = 10, .movementSpeed = 20 };

bool isAlive = true;

void GameManager(void){
    char scoreText[500];
    sprintf(scoreText, "Current Score: %d", player.score);

    DrawText(scoreText, 20, 30, 30, WHITE);
    Player();
    GameOverCheck();
}

void Player(void) {
    if (isAlive == true) {

        //score tester
        if (IsKeyPressed(KEY_K)) {
            player.score+= 10;
        }

        //------------------------------------------------------------
        //      Player rendering and player movement:
        //------------------------------------------------------------

        DrawRectangle(player.position.x, player.position.y, player.SizeX, player.SizeY, WHITE);

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
}

void GameOverCheck(void) {
    if (player.health <= 0) {
        isAlive = false;
        player.health = 0;
        DrawText("Game Over", SCREEN_WIDTH/2 -150, SCREEN_HEIGHT/2, 40, RED);
    }
    //game over test code
    if (IsKeyPressed(KEY_I)) {
        player.health = 0;
    }
}