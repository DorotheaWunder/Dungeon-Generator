#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include "raylib.h"
#include "ui.h"
#include "menu.h"
#include "dungeon.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Inventory UI");
    Dungeon dungeon;

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        dungeon.DrawDungeon();
        DrawMenu();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}