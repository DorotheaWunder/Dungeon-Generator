#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include "raylib.h"
#include "ui.h"
#include "menu.h"
#include "dungeon.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DunGen");
    Dungeon dungeon;

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_SPACE))
        {
            dungeon.GenerateDungeon();
            //dungeon.ResetAlgorithm();
        }

        dungeon.StepPrimAlgorithm();
        dungeon.DrawDungeon();



        EndDrawing();
    }

    CloseWindow();

    return 0;
}