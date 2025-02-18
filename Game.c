//
// Created by theodor on 2025-02-17.
//
#include "raylib.h"
#include <stdio.h>
#include "header.h"

PlayerData player = {
    .position = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2},
    .health = StartHealth, .damage = 10, .score = 0,
    .SizeX = CELL_SIZE,.SizeY = CELL_SIZE, .movementSpeed = CELL_SIZE };

Projectile projectile = {.sizeX = CELL_SIZE /2, .sizeY = CELL_SIZE /2};

char grid [ROWS][COLS];

GameRestarter() {
    player.health = StartHealth;
    GameManager();
}

void GameManager(void){
    char scoreText[500];
    sprintf(scoreText, "Current Score: %d", player.score);
    DrawText(scoreText, 20, 30, 30, WHITE);

    PlayerUpdate();
    GameOverCheck();
}

bool playerIsAlive(void) {
    return player.health > 0;
}

void PlayerUpdate(void) {
    if (playerIsAlive()) {

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
            player.dir = RIGHT;
        } else if (IsKeyPressed(KEY_A)) {
            player.position.x -= player.movementSpeed;
            player.dir = LEFT;
        } else if (IsKeyPressed(KEY_W)) {
            player.position.y -= player.movementSpeed;
            player.dir = UP;
        } else if (IsKeyPressed(KEY_S)) {
            player.position.y += player.movementSpeed;
            player.dir = DOWN;
        }

        //------------------------------------------------------------
        //      Player projectile logic:
        //------------------------------------------------------------

        if (IsKeyPressed(KEY_SPACE)) {
            /*
            if (projectileCooldown >= 0.0f) {
                projectileCooldown = 0.25f;
                ProjectileSpawn(player.position, startingVelocity);
            }
            */

            projectile.isActive = true;
            projectile.isHit = false;

            projectile.position = player.position;

            if (player.dir == RIGHT) {
                projectile.position.x += player.SizeX;
                projectile.velocity = (Vector2){ CELL_SIZE * 2, 0 };
            } else if (player.dir == LEFT) {
                projectile.position.x -= player.SizeX;
                projectile.velocity = (Vector2){ -CELL_SIZE * 2, 0 };
            } else if (player.dir == UP) {
                projectile.position.y += player.SizeY;
                projectile.velocity = (Vector2){ 0, -CELL_SIZE * 2 };
            } else if (player.dir == DOWN) {
                projectile.position.y += player.SizeY;
                projectile.velocity = (Vector2){ 0, CELL_SIZE * 2 };
            }
        }

        if (projectile.isActive == true) {
            projectile.position.x += projectile.velocity.x;
            projectile.position.y += projectile.velocity.y;
            DrawRectangle(projectile.position.x, projectile.position.y, CELL_SIZE / 2, CELL_SIZE / 2, WHITE);
        }
    }
}

void GameOverCheck(void) {
    //game over test code
    if (IsKeyPressed(KEY_I)) {
        player.health = 0;
    }
    if (!playerIsAlive()) {
        DrawText("Game Over", SCREEN_WIDTH/2 -150, SCREEN_HEIGHT/2, 40, RED);

        DrawText("Press Spacebar to restart", SCREEN_WIDTH/2 -325, SCREEN_HEIGHT/2 + 150, 40, GREEN);
        if (IsKeyPressed(KEY_SPACE)) {
            GameRestarter();
        }
    }
}