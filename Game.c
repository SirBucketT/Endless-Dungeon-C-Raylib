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
    printf("Projectiles initialized. MAX_BULLETS: %d\n", MAX_BULLETS);
}

void GameManager(void) {
    char scoreText[500];
    sprintf(scoreText, "Current Score: %d", player.score);
    DrawText(scoreText, 20, 30, 30, WHITE);

    // Debug player info
    DrawText(TextFormat("Player Position: %.0f, %.0f", player.position.x, player.position.y),
             20, 60, 20, GREEN);
    DrawText(TextFormat("Player Direction: %d", player.dir),
             20, 90, 20, GREEN);

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

        // Direction indicator
        Color dirColor = RED;
        switch(player.dir) {
            case RIGHT:
                DrawLineEx((Vector2){player.position.x + player.SizeX, player.position.y + player.SizeY/2},
                          (Vector2){player.position.x + player.SizeX + 20, player.position.y + player.SizeY/2},
                          3, dirColor);
                break;
            case LEFT:
                DrawLineEx((Vector2){player.position.x, player.position.y + player.SizeY/2},
                          (Vector2){player.position.x - 20, player.position.y + player.SizeY/2},
                          3, dirColor);
                break;
            case UP:
                DrawLineEx((Vector2){player.position.x + player.SizeX/2, player.position.y},
                          (Vector2){player.position.x + player.SizeX/2, player.position.y - 20},
                          3, dirColor);
                break;
            case DOWN:
                DrawLineEx((Vector2){player.position.x + player.SizeX/2, player.position.y + player.SizeY},
                          (Vector2){player.position.x + player.SizeX/2, player.position.y + player.SizeY + 20},
                          3, dirColor);
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
                            velocity = (Vector2){CELL_SIZE * 2, 0};
                            break;
                        case LEFT:
                            offset = (Vector2){-player.SizeX - 10, player.SizeY/2};
                            velocity = (Vector2){-CELL_SIZE * 2, 0};
                            break;
                        case UP:
                            offset = (Vector2){player.SizeX/2, -player.SizeY - 10};
                            velocity = (Vector2){0, -CELL_SIZE * 2};
                            break;
                        case DOWN:
                            offset = (Vector2){player.SizeX/2, player.SizeY + 10};
                            velocity = (Vector2){0, CELL_SIZE * 2};
                            break;
                    }

                    projectiles[i].position.x += offset.x;
                    projectiles[i].position.y += offset.y;
                    projectiles[i].velocity = velocity;

                    activeProjectilesCount++;
                    spawned = true;

                    // Visual debug for spawn point
                    DrawCircle(projectiles[i].position.x, projectiles[i].position.y, 5, RED);
                    printf("Projectile spawned at: %.2f, %.2f\n",
                           projectiles[i].position.x, projectiles[i].position.y);
                    break;
                }
            }

            if (!spawned) {
                printf("Failed to spawn projectile. Active count: %d\n", activeProjectilesCount);
            }
        }

        // Projectile update and render
        for (int i = 0; i < MAX_BULLETS; ++i) {
            if (projectiles[i].isActive) {
                projectiles[i].position.x += projectiles[i].velocity.x * GetFrameTime();
                projectiles[i].position.y += projectiles[i].velocity.y * GetFrameTime();

                // Draw projectile with debug info
                DrawRectangle(projectiles[i].position.x - projectiles[i].sizeX/2,
                            projectiles[i].position.y - projectiles[i].sizeY/2,
                            projectiles[i].sizeX, projectiles[i].sizeY, YELLOW);

                DrawText(TextFormat("P%d", i),
                        projectiles[i].position.x - 10,
                        projectiles[i].position.y - 20,
                        20, YELLOW);

                if (projectiles[i].position.x < -CELL_SIZE ||
                    projectiles[i].position.x > SCREEN_WIDTH + CELL_SIZE ||
                    projectiles[i].position.y < -CELL_SIZE ||
                    projectiles[i].position.y > SCREEN_HEIGHT + CELL_SIZE) {
                    projectiles[i].isActive = false;
                    activeProjectilesCount--;
                    printf("Projectile %d destroyed. Active count: %d\n", i, activeProjectilesCount);
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