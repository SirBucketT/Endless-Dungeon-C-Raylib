#ifndef HEADER_H
#define HEADER_H

#define SCREEN_WIDTH    1800
#define SCREEN_HEIGHT   900

#define CELL_SIZE       20
#define ROWS            30
#define COLS            50

#define StartHealth     100

#include "raylib.h"

typedef enum {
    MENU,
    GAME,
    QUIT_GAME,
} GameState;

typedef enum {
    UP,
    DOWN,
    RIGHT,
    LEFT
}direction;

typedef struct {
    Vector2 position;
    int health;
    int damage;
    int score;
    int SizeY;
    int SizeX;
    int movementSpeed;
    direction dir;
}PlayerData;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    int sizeY;
    int sizeX;
    bool isHit;
    bool isActive;
}Projectile;

void ScreenRender(void);
void UserInterface(Texture2D buttonTexture);
void GameManager(void);
void PlayerUpdate(void);
void GameOverCheck(void);
bool playerIsAlive(void);
GameRestarter();

#endif //HEADER_H
