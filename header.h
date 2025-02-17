#ifndef HEADER_H
#define HEADER_H

#define SCREEN_WIDTH    1800
#define SCREEN_HEIGHT   900
#define CELL_SIZE       15
#include "raylib.h"

typedef enum {
    MENU,
    GAME,
    QUIT_GAME,
} GameState;

typedef struct {
    Vector2 position;
    int health;
    int damage;
    int score;
    int SizeY;
    int SizeX;
    int movementSpeed;
}PlayerData;

void ScreenRender(void);
void UserInterface(Texture2D buttonTexture);
void GameManager(void);
void Player(void);
void GameOverCheck(void);

#endif //HEADER_H
