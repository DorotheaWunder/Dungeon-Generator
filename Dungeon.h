#ifndef DUNGEON_H
#define DUNGEON_H

#include <memory>
#include <vector>
#include "LevelTile.h"


class Player;

constexpr int LEVEL_WIDTH = 30;
constexpr int LEVEL_HEIGHT = 30;

struct Anchor
{
    int x;
    int y;

    Anchor(int x = 0, int y = 0) : x{x}, y{y} { }
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

    bool IsValidCell(int x, int y) const;
    std::vector<std::vector<LevelTile>> rooms;

    void GenerateDungeon();
    void SpawnPlayer(Player& player);


private:
    std::vector<std::pair<int, int>> frontier;
    int currentX, currentY;
    int roomCounter;
    bool isGenerating = false;
    int difficulty = 1;

    std::vector<std::pair<int, int>>GetNeighborTile(int x, int y);
    void MarkAsVisited(int x, int y);
    std::pair<int, int> GetRandomNeighbor(std::vector<std::pair<int, int>>& neighbors);

    TileType DistributeRoomTypes();
    void SetRoomType(int x, int y);
    void ProcessNeighbors(int x, int y);
    void FillWalls(int x, int y);
    void PlaceExit();

    std::vector<Anchor> anchors;
    bool HasEnoughSpace(int x, int y, int minDistance, int maxDistance);
    void RandomAnchorPoint(int numAnchors, int minDistance, int maxDistance);
    void CreateOutlineTiles(int anchorX, int anchorY);
    void CreateRooms();
};
#endif //DUNGEON_H
