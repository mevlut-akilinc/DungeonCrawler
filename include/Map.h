#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
#include <string>

class Map
{
    private:
    std::vector<std::vector<Tile>> grid;
    int width;
    int height;

    public:
    Map(int width,int height);
    Tile& getTile(int x , int y );
    void setTile(int x, int y, TileType t );
    void draw(sf::RenderWindow &window);
    void calculateFoV(sf::Vector2i pos, int radius); //Ai destekli yazıldı.

};
