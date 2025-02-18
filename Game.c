
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

Projectile projectiles[MAX_BULLETS];
int activeProjectilesCount = 0;
char grid[ROWS][COLS];

void InitProjectiles(void) {
    for (int i = 0; i < MAX_BULLETS; ++i) {
        projectiles[i].isActive = false;
        projectiles[i].position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        projectiles[i].sizeX = CELL_SIZE / 2;
        projectiles[i].sizeY = CELL_SIZE / 2;
        projectiles[i].velocity = (Vector2){0, 0};
    }
    activeProjectilesCount = 0;
}

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

        //might remove later ***
        player.position.x = Clamp(player.position.x, 0, SCREEN_WIDTH - player.SizeX);
        player.position.y = Clamp(player.position.y, 0, SCREEN_HEIGHT - player.SizeY);

        DrawRectangle(player.position.x, player.position.y, player.SizeX, player.SizeY, WHITE);

        //------------------------------------------------------------
        //      Player projectile logic:
        //------------------------------------------------------------

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
                            offset = (Vector2){player.SizeX + 10, 0};
                            velocity = (Vector2){CELL_SIZE * 2, 0};
                            break;
                        case LEFT:
                            offset = (Vector2){-player.SizeX - 10, 0};
                            velocity = (Vector2){-CELL_SIZE * 2, 0};
                            break;
                        case UP:
                            offset = (Vector2){0, -player.SizeY - 10};
                            velocity = (Vector2){0, -CELL_SIZE * 2};
                            break;
                        case DOWN:
                            offset = (Vector2){0, player.SizeY + 10};
                            velocity = (Vector2){0, CELL_SIZE * 2};
                            break;
                    }

                    projectiles[i].position.x += offset.x;
                    projectiles[i].position.y += offset.y;
                    projectiles[i].velocity = velocity;

                    activeProjectilesCount++;
                    spawned = true;
                    printf("Projectile spawned! Active count: %d\n", activeProjectilesCount);
                    break;
                }
            }

            if (!spawned) {
                printf("Failed to spawn projectile. Active count: %d\n", activeProjectilesCount);
            }
        }

        //------------------------------------------------------------
        //      Projectile movement and rendering:
        //------------------------------------------------------------

        for (int i = 0; i < MAX_BULLETS; ++i) {
            if (projectiles[i].isActive) {
                projectiles[i].position.x += projectiles[i].velocity.x * GetFrameTime();
                projectiles[i].position.y += projectiles[i].velocity.y * GetFrameTime();

                DrawRectangle(projectiles[i].position.x, projectiles[i].position.y, 
                            projectiles[i].sizeX, projectiles[i].sizeY, YELLOW);

                if (projectiles[i].position.x < -CELL_SIZE ||
                    projectiles[i].position.x > SCREEN_WIDTH + CELL_SIZE ||
                    projectiles[i].position.y < -CELL_SIZE ||
                    projectiles[i].position.y > SCREEN_HEIGHT + CELL_SIZE) {
                    projectiles[i].isActive = false;
                    activeProjectilesCount--;
                    printf("Projectile destroyed. Active count: %d\n", activeProjectilesCount);
                }
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
    InitProjectiles();
}