#ifndef HEADER_H
#define HEADER_H

#define SCREEN_WIDTH    1800
#define SCREEN_HEIGHT   900

#define WIDTH           89
#define HEIGHT          40
#define CELL_SIZE       20

#define CELL_SIZE       20
#define ROWS            (SCREEN_HEIGHT / CELL_SIZE)
#define COLS            (SCREEN_WIDTH / CELL_SIZE)

#define StartHealth     100
#define MAX_BULLETS     20

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
} direction;

typedef struct {
    Vector2 position;
    int health;
    int damage;
    int score;
    int SizeY;
    int SizeX;
    int movementSpeed;
    direction dir;
} PlayerData;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    int sizeY;
    int sizeX;
    bool isHit;
    bool isActive;
} Projectile;

void ScreenRender(void);
void UserInterface(Texture2D buttonTexture);
void GameManager(void);
void PlayerUpdate(void);
void GameOverCheck(void);
bool playerIsAlive(void);
void GameRestarter(void);
void InitializeProjectiles(void);

#endif // HEADER_H
