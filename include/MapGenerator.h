#pragma once
#include "Map.h"
#include <vector>

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

    std::vector<sf::IntRect> collectedRooms; // generate() sırasında doldurulur
    unsigned int lastSeed = 0;

    void split(BSPNode* node);
    void createRooms(BSPNode* node, Map& map);
    void connectRooms(BSPNode* node, Map& map);
    sf::Vector2i getRoomCenter(BSPNode* node);
    static void deleteTree(BSPNode* node);

public:
    Map* generate(int width, int height);

    // Üretilen odaların listesi — düşman yerleştirme için kullanılır
    const std::vector<sf::IntRect>& getRooms() const { return collectedRooms; }

    // Kayıt/yükleme için son üretimde kullanılan seed
    unsigned int getLastSeed() const { return lastSeed; }
};
