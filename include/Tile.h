#pragma once
#include <SFML/Graphics.hpp>

enum class TileType
{
    WALL,
    FLOOR,
    WATER,
    STAIRS
};

class Tile
{
private:
    TileType type;
    bool walkable;
    bool visible;
    bool explored;

public:
    Tile(TileType type, bool walkable)
    {
        this->type = type;
        this->walkable = walkable;
        this->visible = false;
        this->explored = false; // Bu degerler baslangıçta false olarak atıyoruz
    }
    bool isWalkable()
    { // Constructor oluşturma islemi
        return walkable;
    }

    bool isVisible()
    {
        return visible;
    }
    void draw(sf::RenderWindow &window)
    {
    }
};
