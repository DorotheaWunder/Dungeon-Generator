#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Dungeon;

class Player
{
public:
    int posX;
    int posY;

    //--- draw, move
    void DrawPlayer();
    void MovePlayer(int dirX, int dirY, const Dungeon& dungeon);

    Player();

private:
    float playerSize;
    Color playerColor;
    Color outlineColor;
};



#endif //PLAYER_H
