#include <iostream>
#include <stdlib.h>
#include "raylib.h"
#include "ui.h"
#include "menu.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Inventory UI");



    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawMenu();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}