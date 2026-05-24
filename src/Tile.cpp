#include "Tile.h"

void Tile::draw(sf::RenderWindow& window, int x, int y)
{
    // Hiç keşfedilmemişse çizme — pencere siyah kalır
    if (!explored) return;

    sf::RectangleShape shape(sf::Vector2f(32.f, 32.f));

    // visible → tam renk | explored ama karanlık → soluk renk
    switch (type)
    {
        case TileType::WALL:
            shape.setFillColor(visible ? sf::Color(100, 100, 100) : sf::Color(35, 35, 35));
            break;
        case TileType::FLOOR:
            shape.setFillColor(visible ? sf::Color(60,  55,  50)  : sf::Color(20, 18, 16));
            break;
        case TileType::WATER:
            shape.setFillColor(visible ? sf::Color(30,  80,  180) : sf::Color(10, 28, 60));
            break;
        case TileType::STAIRS:
            shape.setFillColor(visible ? sf::Color(180, 150, 50)  : sf::Color(60, 50, 15));
            break;
    }

    shape.setPosition(x * 32.f, y * 32.f);
    window.draw(shape);
}
