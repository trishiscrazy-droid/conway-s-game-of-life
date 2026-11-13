#include "include/raylib.h"
#include <iostream>
#include <random>

using namespace std;

class Grid 
{
public:
    bool alive = false;
};

constexpr int gridSIDE = 50;
constexpr int gridCOUNT = 20;

Grid grid[gridCOUNT][gridCOUNT] {0, false};
Grid nextgrid[gridCOUNT][gridCOUNT] {0, false};

Color myBLACK = {0, 0, 0, 230};
Color myRAYWHITE = {245, 245, 245, 150};

const Vector2 origin = {gridSIDE, gridSIDE};
int gridAlive = 0;

void InitGrid() 
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 10);

    for (int i = 0; i < gridCOUNT; i++)
    {
        for (int j = 0; j < gridCOUNT; j++)
        {
            grid[i][j].alive = (dist(gen) <= 2);
            if (!grid[i][j].alive)
            {
                DrawRectangleLines(origin.x + gridSIDE*i, origin.y + gridSIDE*j, gridSIDE, gridSIDE, myRAYWHITE);
            } else {
                DrawRectangle(origin.x + gridSIDE*i, origin.y + gridSIDE*j, gridSIDE, gridSIDE, myRAYWHITE);
                gridAlive++;
            }
        }
    }    
}

unsigned int CountAliveNeighbours(int i, int j) 
{
    int count = 0;
    int alpha = -1;
    int beta = -1;
    for (; alpha <= 1; alpha++) 
    {
        if (!i && alpha == -1)
            {
               alpha++;                
            }
        if ((i == gridCOUNT - 1) && (alpha == 1))
            {   
                break;   
            }
        for (; beta <= 1; beta++)
        {
            if ((!j) && beta == -1)
            {
                beta++;
            }
            if (((j == gridCOUNT - 1) && (beta == 1)) || !(alpha || beta))
            {
                continue;
            }
            if (grid[i+alpha][j+beta].alive) {
                count++;
            }
        }
        beta = -1;
    }
    return count;
}

void UpdateGrid() 
{
    for (int i = 0; i < gridCOUNT; i++)
    {
        for (int j = 0; j < gridCOUNT; j++)
        {
            unsigned int nalive = CountAliveNeighbours(i, j);
            if (nalive < 2 || nalive > 3)
            {
                nextgrid[i][j].alive = false; 
            }
            if (nalive == 2)
            {
                nextgrid[i][j].alive = grid[i][j].alive;
            }
            if (nalive == 3)
            {
                nextgrid[i][j].alive = true;
            }
        }
    }
    for (int i = 0; i < gridCOUNT; i++)
    {
        for (int j = 0; j < gridCOUNT; j++) 
        {
            grid[i][j] = nextgrid[i][j];
        }
    }
}

void DrawGrid()
{
    gridAlive = 0;
    for (int i = 0; i < gridCOUNT; i++)
    {
        for (int j = 0; j < gridCOUNT; j++)
        {
            if (!grid[i][j].alive)
            {
                DrawRectangleLines(origin.x + gridSIDE*i, origin.y + gridSIDE*j, gridSIDE, gridSIDE, RAYWHITE);
            } else {
                DrawRectangle(origin.x + gridSIDE*i, origin.y + gridSIDE*j, gridSIDE, gridSIDE, RAYWHITE);
                gridAlive++;
            }
        }
    }    
}

int main(int argc, char** argv) {
    
    unsigned int fps = 5;
    if (argc > 1)
    {
        try 
        {   
            fps = stoi(argv[1]);
        }
        catch (const invalid_argument& e)
        {
            cout << "Please Enter a Valid Integer!!!" << endl;
            exit(1);
        }
    }
    if (fps <= 0) {
        fps = 5;
    }
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED);
    
    InitWindow(gridSIDE*(gridCOUNT+2), gridSIDE*(gridCOUNT+2), "CONWAY's GAME OF LIFE");
    SetTargetFPS(fps);

    InitGrid();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(myBLACK);

        UpdateGrid();
        DrawGrid();
        DrawText(TextFormat("Alive Grids: %d", gridAlive), 0, 0, 25, RAYWHITE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}