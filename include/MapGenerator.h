#pragma once
#include "Map.h"
#include <memory>

struct BSPNode
{
    sf::IntRect area;           // Bu node'un kapladığı alan
    BSPNode* left  = nullptr;   // Sol çocuk
    BSPNode* right = nullptr;   // Sağ çocuk
    sf::IntRect room;           // Sadece yaprak node'larda dolu
};

class MapGenerator
{
private:
    static const int MIN_SIZE = 6;  // Minimum bölünebilir alan

    void split(BSPNode* node);
    void createRooms(BSPNode* node, Map& map);
    void connectRooms(BSPNode* node, Map& map);
    sf::Vector2i getRoomCenter(BSPNode* node);

public:
    Map* generate(int width, int height);
};
