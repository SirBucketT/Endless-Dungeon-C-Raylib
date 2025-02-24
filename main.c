/*#include <stdio.h>
#include "header.h"

int main(void) {
    ScreenRender();
    return 0;
}*/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

typedef struct {
    int x, y;
    int visited;
    int walls[4];
} Cell;

Cell grid[WIDTH * HEIGHT];

int getIndex(int x, int y) {
    if(x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return -1;
    return x + y * WIDTH;
}

// Removes the wall between two adjacent cells a and b.
void removeWall(Cell *a, Cell *b) {
    int dx = b->x - a->x;
    int dy = b->y - a->y;
    if(dx == 1) {
        a->walls[1] = 0;
        b->walls[3] = 0;
    } else if(dx == -1) {
        a->walls[3] = 0;
        b->walls[1] = 0;
    } else if(dy == 1) {
        a->walls[2] = 0;
        b->walls[0] = 0;
    } else if(dy == -1) {
        a->walls[0] = 0;
        b->walls[2] = 0;
    }
}

int stack[WIDTH * HEIGHT];
int stackSize = 0;
bool mazeGenerationComplete = false;

void MazeGeneration() {
    //if maze is generrated return
    if(stackSize == 0) {
        mazeGenerationComplete = true;
        return;
    }

    // Look at the current cell
    int currentIndex = stack[stackSize - 1];
    int x = grid[currentIndex].x;
    int y = grid[currentIndex].y;

    int neighbors[4];
    int neighborCount = 0;

    // Check the cell above
    int neighborIndex = getIndex(x, y - 1);
    if(neighborIndex != -1 && !grid[neighborIndex].visited) {
        neighbors[neighborCount++] = neighborIndex;
    }

    // Check the cell to the right
    neighborIndex = getIndex(x + 1, y);
    if(neighborIndex != -1 && !grid[neighborIndex].visited) {
        neighbors[neighborCount++] = neighborIndex;
    }

    // Check the cell below
    neighborIndex = getIndex(x, y + 1);
    if(neighborIndex != -1 && !grid[neighborIndex].visited) {
        neighbors[neighborCount++] = neighborIndex;
    }

    // Check the cell to the left
    neighborIndex = getIndex(x - 1, y);
    if(neighborIndex != -1 && !grid[neighborIndex].visited) {
        neighbors[neighborCount++] = neighborIndex;
    }

    if(neighborCount > 0) {
        // If there are unvisited neighbors, pick one randomly.
        int randIndex = rand() % neighborCount;
        int chosenNeighbor = neighbors[randIndex];

        // Remove the wall between the current cell and the chosen neighbor.
        removeWall(&grid[currentIndex], &grid[chosenNeighbor]);

        // Mark the chosen neighbor as visited.
        grid[chosenNeighbor].visited = 1;

        // Push the chosen neighbor onto the stack.
        stack[stackSize++] = chosenNeighbor;
    } else {
        // If there are no unvisited neighbors, backtrack by popping the stack.
        stackSize--;
    }
}

void initializeGrid() {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            int gridIndexer = getIndex(x, y);
            grid[gridIndexer].x = x;
            grid[gridIndexer].y = y;
            grid[gridIndexer].visited = 0;
            grid[gridIndexer].walls[0] = 1;
            grid[gridIndexer].walls[1] = 1;
            grid[gridIndexer].walls[2] = 1;
            grid[gridIndexer].walls[3] = 1;
        }
    }
    stackSize = 0;
    grid[0].visited = 1;
    stack[stackSize++] = 0;
    mazeGenerationComplete = false;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Maze Generation McThingy");

    srand(time(NULL));

    initializeGrid();

    int mazeWidthPixels = WIDTH * CELL_SIZE;
    int mazeHeightPixels = HEIGHT * CELL_SIZE;
    int originX = (SCREEN_WIDTH - mazeWidthPixels) / 2;
    int originY = (SCREEN_HEIGHT - mazeHeightPixels) / 2;

    while(!WindowShouldClose()) {
        if(!mazeGenerationComplete) {
            MazeGeneration();
        }
        if(IsKeyPressed(KEY_SPACE)) {
            initializeGrid();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for(int i = 0; i < WIDTH * HEIGHT; i++) {
            int cellX = grid[i].x * CELL_SIZE + originX;
            int cellY = grid[i].y * CELL_SIZE + originY;

            if(grid[i].walls[0])
                DrawLine(cellX, cellY, cellX + CELL_SIZE, cellY, RAYWHITE);
            if(grid[i].walls[1])
                DrawLine(cellX + CELL_SIZE, cellY, cellX + CELL_SIZE, cellY + CELL_SIZE, RAYWHITE);
            if(grid[i].walls[2])
                DrawLine(cellX + CELL_SIZE, cellY + CELL_SIZE, cellX, cellY + CELL_SIZE, RAYWHITE);
            if(grid[i].walls[3])
                DrawLine(cellX, cellY + CELL_SIZE, cellX, cellY, RAYWHITE);
        }

        //code that shows an indication of where the maze is being drawn
        if(stackSize > 0) {
            int currentIndex = stack[stackSize - 1];
            int currentX = grid[currentIndex].x * CELL_SIZE + originX;
            int currentY = grid[currentIndex].y * CELL_SIZE + originY;
            DrawRectangle(currentX + 2, currentY + 2, CELL_SIZE - 4, CELL_SIZE - 4, YELLOW);
        }

        // start color set to green
        DrawRectangle(grid[0].x * CELL_SIZE + originX + 2,
                      grid[0].y * CELL_SIZE + originY + 2,
                      CELL_SIZE - 4, CELL_SIZE - 4, GREEN);
        //end color of maze set to red.
        DrawRectangle(grid[WIDTH * HEIGHT - 1].x * CELL_SIZE + originX + 2,
                      grid[WIDTH * HEIGHT - 1].y * CELL_SIZE + originY + 2,
                      CELL_SIZE - 4, CELL_SIZE - 4, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}