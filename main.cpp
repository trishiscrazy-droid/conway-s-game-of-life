#include "include/raylib.h"
#include <iostream>
#include <random>

using namespace std;

class Grid 
{
public:
    unsigned int neighboursalive = 0;
    bool alive = false;
};

constexpr int gridSIDE = 50;
constexpr int gridCOUNT = 20;

Grid grid[gridCOUNT][gridCOUNT] {0, false};
Color myBLACK = {0, 0, 0, 230};
Color myRAYWHITE = {245, 245, 245, 150};
Vector2 origin = {gridSIDE, gridSIDE};

void InitGrid() 
{
    for (int i = 0; i < gridCOUNT; i++)
    {
        for (int j = 0; j < gridCOUNT; j++)
        {
            if (!grid[i][j].alive)
            {
                DrawRectangleLines(origin.x + gridSIDE*i, origin.y + gridSIDE*j, gridSIDE, gridSIDE, RAYWHITE);
            } else {
                DrawRectangle(origin.x + gridSIDE*i, origin.y + gridSIDE*j, gridSIDE, gridSIDE, RAYWHITE);
            }
        }
    }    
}
int main() {

    random_device rd;
    uniform_int_distribution<int> dist(1, 9);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED);
    
    InitWindow(gridSIDE*(gridCOUNT+2), gridSIDE*(gridCOUNT+2), "CONWAY's GAME OF LIFE");
    SetTargetFPS(60);

    grid[10][15].alive = true;
    while (!WindowShouldClose())
    {
        for (int i = 0; i < gridCOUNT; i++)
        {
            for (int j = 0; j < gridCOUNT; j++)
            {
                if (grid[i][j].alive) {
                    DrawRectangle(origin.x + gridSIDE*i, origin.y + gridSIDE*j, gridSIDE, gridSIDE, myRAYWHITE);
                }
            }
        }
        BeginDrawing();
        ClearBackground(myBLACK);
        InitGrid();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}