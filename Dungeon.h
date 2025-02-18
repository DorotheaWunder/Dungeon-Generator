#ifndef DUNGEON_H
#define DUNGEON_H

constexpr int LEVEL_WIDTH = 20;
constexpr int LEVEL_HEIGHT = 20;

class Dungeon
{
private:
    std::unique_ptr<std::unique_ptr<LevelRoom[]>[]> rooms;

public:
    Dungeon();
    void InitLevelGrid();
    void DrawDungeon();

    LevelRoom* GetRoom(int x, int y) { return &rooms[x][y]; }
    static int GetLevelWidth() { return LEVEL_WIDTH; }
    static int GetLevelHeight() { return LEVEL_HEIGHT; }
};

#endif //DUNGEON_H
