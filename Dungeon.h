#ifndef DUNGEON_H
#define DUNGEON_H

#include <memory>
#include <vector>
#include "LevelRoom.h"

constexpr int LEVEL_WIDTH = 10;
constexpr int LEVEL_HEIGHT = 10;

class Dungeon
{
public:
    Dungeon();
    void InitLevelGrid();
    void DrawDungeon();
    void StepPrimAlgorithm();
    void ResetAlgorithm();


private:
    std::vector<std::vector<LevelRoom>> rooms;
    std::vector<std::pair<int, int>> frontier;
    int currentX, currentY;
    int roomCounter;
    bool isGenerating = false;

    std::vector<std::pair<int, int>>GetNeighborTile(int x, int y);
    void MarkAsVisited(int x, int y);
    std::pair<int, int> GetRandomNeighbor(std::vector<std::pair<int, int>>& neighbors);
    bool IsValidCell(int x, int y) const;
    void SetRoomType(int x, int y);
    void ProcessNeighbors(int x, int y);
    void FillWalls(int x, int y);
    void PlaceExit();
};

#endif //DUNGEON_H
