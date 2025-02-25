#ifndef DUNGEON_H
#define DUNGEON_H

#include <memory>
#include <vector>
#include "LevelTile.h"

constexpr int LEVEL_WIDTH = 30;
constexpr int LEVEL_HEIGHT = 30;

struct Anchor
{
    int x;
    int y;

    Anchor(int x = 0, int y = 0);
};

int CalculateSquareDistance(const Anchor& a1, const Anchor& a2);

class Dungeon
{
public:
    Dungeon();
    void InitLevelGrid();
    void DrawDungeon();
    void StepPrimAlgorithm();
    void ResetAlgorithm();

    void RandomAnchorPoint(int numAnchors, int minDistance, int maxDistance);
    void GenerateDungeon();


private:
    std::vector<std::vector<LevelTile>> rooms;
    std::vector<std::pair<int, int>> frontier;
    int currentX, currentY;
    int roomCounter;
    bool isGenerating = false;

    std::vector<std::pair<int, int>>GetNeighborTile(int x, int y);
    void MarkAsVisited(int x, int y);
    std::pair<int, int> GetRandomNeighbor(std::vector<std::pair<int, int>>& neighbors);
    bool IsValidCell(int x, int y) const;
    TileType DistributeRoomTypes();
    void SetRoomType(int x, int y);
    void ProcessNeighbors(int x, int y);
    void FillWalls(int x, int y);
    void PlaceExit();

    std::vector<Anchor> anchors;
    bool HasEnoughSpace(int x, int y, int minDistance, int maxDistance);
    //void RandomAnchorPoint(int numAnchors, int minDistance, int maxDistance);
    void CreateOutlineTiles(int anchorX, int anchorY);
    void CreateRooms();


    //void GenerateDungeon();
};
#endif //DUNGEON_H
