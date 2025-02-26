#include "LevelTile.h"
#include "Dungeon.h"
#include "raylib.h"
#include "player.h"

Player::Player()
    : posX(0), posY(0), playerSize(20.0f), playerColor(GREEN), outlineColor(WHITE) {}

void Player::DrawPlayer()
{
    float centerX = posX * playerSize + playerSize / 2;
    float centerY = posY * playerSize + playerSize / 2;
    float radius = playerSize / 3;

    DrawCircle(centerX, centerY, radius, playerColor);
    DrawCircleLines(centerX, centerY, radius, outlineColor);
}

void Player::MovePlayer(int dirX, int dirY, const Dungeon& dungeon)
{
    int newPosX = posX + dirX;
    int newPosY = posY + dirY;

    if (dungeon.IsValidCell(newPosX, newPosY)&&
        dungeon.rooms[newPosX][newPosY].roomType != TileType::WALL)
    {
        posX = newPosX;
        posY = newPosY;
    }
}
