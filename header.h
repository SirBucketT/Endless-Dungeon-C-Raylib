#ifndef HEADER_H
#define HEADER_H

#define SCREEN_WIDTH    1800
#define SCREEN_HEIGHT   900
#include "raylib.h"

typedef enum {
    MENU,
    GAME
} GameState;

//GameState currentState;

void ScreenRender(void);
void UserInterface(Texture2D buttonTexture);

#endif //HEADER_H
