#include "raylib.h"
#include <stdio.h>
#include "header.h"
#include "raymath.h"

PlayerData player = {
    .position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
    .health = StartHealth,
    .damage = 10,
    .score = 0,
    .SizeX = CELL_SIZE,
    .SizeY = CELL_SIZE,
    .movementSpeed = CELL_SIZE,
    .dir = RIGHT
};

Projectile projectiles[MAX_BULLETS] = {
    { .isActive = false, .isHit = false, .sizeX = CELL_SIZE/2, .sizeY = CELL_SIZE/2 },
};

int bulletSpeed = 40;

int activeProjectilesCount = 0;
char grid[ROWS][COLS];



void GameManager(void) {
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
        // score tester
        if (IsKeyPressed(KEY_K)) {
            player.score += 10;
        }

        //------------------------------------------------------------
        //      Player rendering and player movement:
        //------------------------------------------------------------

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

        player.position.x = Clamp(player.position.x, 0, SCREEN_WIDTH - player.SizeX);
        player.position.y = Clamp(player.position.y, 0, SCREEN_HEIGHT - player.SizeY);

        // Draw player with direction indicator
        DrawRectangle(player.position.x, player.position.y, player.SizeX, player.SizeY, WHITE);

        Color DirectionArrow = RED;
        switch(player.dir) {
            case RIGHT:
                DrawLineEx((Vector2){player.position.x + player.SizeX, player.position.y + player.SizeY/2},
                          (Vector2){player.position.x + player.SizeX + 20, player.position.y + player.SizeY/2},
                          3, DirectionArrow);
                break;
                    case LEFT:
                DrawLineEx((Vector2){player.position.x, player.position.y + player.SizeY/2},
                          (Vector2){player.position.x - 20, player.position.y + player.SizeY/2},
                          3, DirectionArrow);
                break;
            case UP:
                DrawLineEx((Vector2){player.position.x + player.SizeX/2, player.position.y},
                          (Vector2){player.position.x + player.SizeX/2, player.position.y - 20},
                          3, DirectionArrow);
                break;
            case DOWN:
                DrawLineEx((Vector2){player.position.x + player.SizeX/2, player.position.y + player.SizeY},
                          (Vector2){player.position.x + player.SizeX/2, player.position.y + player.SizeY + 20},
                          3, DirectionArrow);
                break;
        }

        // Projectile spawning
        if (IsKeyPressed(KEY_SPACE) && activeProjectilesCount < MAX_BULLETS) {
            bool spawned = false;
            for (int i = 0; i < MAX_BULLETS; ++i) {
                if (!projectiles[i].isActive) {
                    projectiles[i].isActive = true;
                    projectiles[i].isHit = false;
                    projectiles[i].position = player.position;

                    Vector2 offset = {0, 0};
                    Vector2 velocity = {0, 0};

                    switch(player.dir) {
                        case RIGHT:
                            offset = (Vector2){player.SizeX + 10, player.SizeY/2};
                            velocity = (Vector2){CELL_SIZE * bulletSpeed, 0};
                            break;
                        case LEFT:
                            offset = (Vector2){-player.SizeX - 10, player.SizeY/2};
                            velocity = (Vector2){-CELL_SIZE * bulletSpeed, 0};
                            break;
                        case UP:
                            offset = (Vector2){player.SizeX/2, -player.SizeY - 10};
                            velocity = (Vector2){0, -CELL_SIZE * bulletSpeed};
                            break;
                        case DOWN:
                            offset = (Vector2){player.SizeX/2, player.SizeY + 10};
                            velocity = (Vector2){0, CELL_SIZE * bulletSpeed};
                            break;
                    }

                    projectiles[i].position.x += offset.x;
                    projectiles[i].position.y += offset.y;
                    projectiles[i].velocity = velocity;

                    activeProjectilesCount++;
                    spawned = true;
                    break;
                }
            }

        }

            //-----------------------------------------------------
            //      Player projectile rendering and update
            //-----------------------------------------------------

        for (int i = 0; i < MAX_BULLETS; ++i) {

            if (!projectiles[i].isActive) {
                continue;
            }

            projectiles[i].position.x += projectiles[i].velocity.x * GetFrameTime();
            projectiles[i].position.y += projectiles[i].velocity.y * GetFrameTime();

                DrawRectangle(projectiles[i].position.x,
                            projectiles[i].position.y,
                            projectiles->sizeX, projectiles->sizeY, WHITE);


                if (projectiles[i].position.x < -CELL_SIZE ||
                    projectiles[i].position.x > SCREEN_WIDTH + CELL_SIZE ||
                    projectiles[i].position.y < -CELL_SIZE ||
                    projectiles[i].position.y > SCREEN_HEIGHT + CELL_SIZE) {
                    projectiles[i].isActive = false;
                    activeProjectilesCount--;
                }
        }
    }
}

void GameOverCheck(void) {
    if (IsKeyPressed(KEY_I)) {
        player.health = 0;
    }
    if (!playerIsAlive()) {
        DrawText("Game Over", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 40, RED);
        DrawText("Press Spacebar to restart", SCREEN_WIDTH / 2 - 325, SCREEN_HEIGHT / 2 + 150, 40, GREEN);
        if (IsKeyPressed(KEY_SPACE)) {
            GameRestarter();
        }
    }
}

void GameRestarter(void) {
    player.health = StartHealth;
    player.score = 0;
    player.position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    player.dir = RIGHT;
}