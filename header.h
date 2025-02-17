#ifndef HEADER_H
#define HEADER_H

#define SCREEN_WIDTH    1800
#define SCREEN_HEIGHT   900
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
}PlayerData;

void ScreenRender(void);
void UserInterface(Texture2D buttonTexture);
void GameManager(void);
void Player(void);

#endif //HEADER_H
