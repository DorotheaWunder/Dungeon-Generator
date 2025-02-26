#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include "raylib.h"
#include "dungeon.h"
#include "player.h"

int main()
{
    InitWindow(620, 620, "DunGen");
    Dungeon dungeon;
    Player player;

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_W)) player.MovePlayer(0, -1, dungeon);
        if (IsKeyPressed(KEY_S)) player.MovePlayer(0, 1, dungeon);
        if (IsKeyPressed(KEY_A)) player.MovePlayer(-1, 0, dungeon);
        if (IsKeyPressed(KEY_D)) player.MovePlayer(1, 0, dungeon);

        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_SPACE))
        {
            dungeon.GenerateDungeon();
            //dungeon.ResetAlgorithm(); //--> the one with the cool step by step animation (only maze though)
            dungeon.SpawnPlayer(player);

        }

        if (dungeon.rooms[player.posX][player.posY].roomType == TileType::EXIT)
        {
            dungeon.GenerateDungeon();
            dungeon.SpawnPlayer(player);
        }

        dungeon.StepPrimAlgorithm();
        dungeon.DrawDungeon();

        player.DrawPlayer();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}