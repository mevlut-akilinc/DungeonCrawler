#include "Map.h"

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;

    grid.resize(height, std::vector<Tile>(width, Tile(TileType::WALL, false)));
}

Tile& Map::getTile(int x, int y)
{
    return grid[y][x];
}

void Map::setTile(int x, int y, TileType t)
{
    bool walkable = (t == TileType::FLOOR || t == TileType::STAIRS);
    grid[y][x] = Tile(t, walkable);
}

void Map::draw(sf::RenderWindow& window)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            grid[y][x].draw(window, x, y);
}

void Map::calculateFoV(sf::Vector2i pos, int radius)
{
    // Şimdilik boş, ilerleyen günlerde dolduracağız
}
