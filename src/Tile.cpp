#include "Tile.h"

void Tile::draw(sf::RenderWindow& window, int x, int y)
{
    sf::RectangleShape shape(sf::Vector2f(32.f, 32.f));

    switch (type)
    {
        case TileType::WALL:
            shape.setFillColor(sf::Color(80, 80, 80));
            break;
        case TileType::FLOOR:
            shape.setFillColor(sf::Color(40, 40, 40));
            break;
        case TileType::WATER:
            shape.setFillColor(sf::Color(30, 80, 180));
            break;
        case TileType::STAIRS:
            shape.setFillColor(sf::Color(180, 150, 50));
            break;
    }

    shape.setPosition(x * 32.f, y * 32.f);
    window.draw(shape);
}
