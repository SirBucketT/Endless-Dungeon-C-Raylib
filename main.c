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

#define WIDTH 50
#define HEIGHT 30
#define CELL_SIZE 25

typedef struct {
    int x, y;
    int visited;
    int walls[4];       // Walls around the cell: index 0=top, 1=right, 2=bottom, 3=left (1 = wall exists)
} Cell;

Cell grid[WIDTH * HEIGHT];

// Convert 2D grid coordinates into a 1D array index
int getIndex(int x, int y) {
    if(x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return -1;      // Return -1 if the coordinates are out of bounds
    return x + y * WIDTH;
}

// Remove the wall between two adjacent cells
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

//-------------------------------------------------------------------------------
// Recursive backtracking function to generate the maze.
// Instead of computing neighbors only once, we recalc them each time so that
// we never try to process an already visited cell.
//-------------------------------------------------------------------------------
void generateMaze(int currentIndex) {
    grid[currentIndex].visited = 1;   // Mark the current cell as visited

    // Repeat until there are no unvisited neighbors left for this cell.
    while (1) {
        int neighbors[4];  // Array to hold indices of valid unvisited neighbors
        int neighborCount = 0;

        int x = grid[currentIndex].x;
        int y = grid[currentIndex].y;

        // Check the neighbor above (up)
        int neighborIndex = getIndex(x, y - 1);
        if(neighborIndex != -1 && !grid[neighborIndex].visited) {
            neighbors[neighborCount++] = neighborIndex;
        }
        // Check the neighbor to the right
        neighborIndex = getIndex(x + 1, y);
        if(neighborIndex != -1 && !grid[neighborIndex].visited) {
            neighbors[neighborCount++] = neighborIndex;
        }
        // Check the neighbor below (down)
        neighborIndex = getIndex(x, y + 1);
        if(neighborIndex != -1 && !grid[neighborIndex].visited) {
            neighbors[neighborCount++] = neighborIndex;
        }
        // Check the neighbor to the left
        neighborIndex = getIndex(x - 1, y);
        if(neighborIndex != -1 && !grid[neighborIndex].visited) {
            neighbors[neighborCount++] = neighborIndex;
        }

        // If there are no unvisited neighbors, break out of the loop
        if(neighborCount == 0) {
            break;
        }

        // Choose a random neighbor from the list of available ones
        int randIndex = rand() % neighborCount;
        int chosenNeighbor = neighbors[randIndex];

        // Remove the wall between the current cell and the chosen neighbor
        removeWall(&grid[currentIndex], &grid[chosenNeighbor]);

        // Recursively generate the maze from the chosen neighbor
        generateMaze(chosenNeighbor);
    }
}

// Initialize the maze grid: set cell coordinates, mark as unvisited, and add walls
void initializeGrid() {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            int idx = getIndex(x, y);  // Convert 2D coordinates to a 1D index
            grid[idx].x = x;
            grid[idx].y = y;
            grid[idx].visited = 0;
            // Initially, every cell has all four walls
            grid[idx].walls[0] = 1;  // Top wall
            grid[idx].walls[1] = 1;  // Right wall
            grid[idx].walls[2] = 1;  // Bottom wall
            grid[idx].walls[3] = 1;  // Left wall
        }
    }
}

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Endless dungeon using recursive and origin shift");
    SetTargetFPS(60);   // Run the game loop at 60 FPS

    srand(time(NULL));  // Seed the random number generator

    initializeGrid();   // Initialize the grid with cells and walls
    generateMaze(0);    // Generate the maze starting from cell at index 0 (top-left)

    // Calculate the pixel dimensions of the maze and compute an origin shift
    int mazeWidthPixels = WIDTH * CELL_SIZE;
    int mazeHeightPixels = HEIGHT * CELL_SIZE;
    int originX = (SCREEN_WIDTH - mazeWidthPixels) / 2;
    int originY = (SCREEN_HEIGHT - mazeHeightPixels) / 2;

    while (!WindowShouldClose()) {
        // Regenerate the maze when the spacebar is pressed
        if (IsKeyPressed(KEY_SPACE)) {
            initializeGrid();
            generateMaze(0);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the maze: apply the origin shift to each cell's drawing position
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            int cellX = grid[i].x * CELL_SIZE + originX;
            int cellY = grid[i].y * CELL_SIZE + originY;

            // Draw the top wall if it exists
            if (grid[i].walls[0])
                DrawLine(cellX, cellY, cellX + CELL_SIZE, cellY, BLACK);
            // Draw the right wall if it exists
            if (grid[i].walls[1])
                DrawLine(cellX + CELL_SIZE, cellY, cellX + CELL_SIZE, cellY + CELL_SIZE, BLACK);
            // Draw the bottom wall if it exists
            if (grid[i].walls[2])
                DrawLine(cellX + CELL_SIZE, cellY + CELL_SIZE, cellX, cellY + CELL_SIZE, BLACK);
            // Draw the left wall if it exists
            if (grid[i].walls[3])
                DrawLine(cellX, cellY + CELL_SIZE, cellX, cellY, BLACK);
        }

        //starting point in maze
        DrawRectangle(grid[0].x * CELL_SIZE + originX + 2, grid[0].y * CELL_SIZE + originY + 2,
                      CELL_SIZE - 4, CELL_SIZE - 4, GREEN);

        //exit point in maze
        DrawRectangle(grid[WIDTH * HEIGHT - 1].x * CELL_SIZE + originX + 2,
                      grid[WIDTH * HEIGHT - 1].y * CELL_SIZE + originY + 2,
                      CELL_SIZE - 4, CELL_SIZE - 4, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
