#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Tile.h"
#include "Item.h"
#include "Chest.h"

class Map
{
private:
    std::vector<std::vector<Tile>> grid;
    int width;
    int height;

    std::map<std::pair<int,int>, Item*>  itemsOnGround;
    std::vector<Chest*>                  chests;

public:
    Map(int width, int height);
    Tile& getTile(int x, int y);
    void setTile(int x, int y, TileType t);
    void draw(sf::RenderWindow& window);
    void resetVisibility();
    void calculateFoV(sf::Vector2i pos, int radius);

    void  placeItem(int x, int y, Item* item);
    Item* pickupItem(int x, int y);

    void   addChest(Chest* chest);
    Chest* getChestAt(int x, int y);  // o pozisyonda chest varsa döndür

    ~Map();
};
