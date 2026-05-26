#include "Tile.h"
#include "TextureManager.h"

// colored_packed.png — 16x16 tile, scale 2x = 32px ekranda
// IntRect(col*16, row*16, 16, 16)
static sf::IntRect rectFor(TileType type)
{
    switch (type)
    {
        case TileType::FLOOR:  return sf::IntRect(288, 0,  16, 16); // (18,0)
        case TileType::WALL:   return sf::IntRect(128, 48, 16, 16); // (8,3)
        case TileType::WATER:  return sf::IntRect(128, 64, 16, 16); // (8,4)
        case TileType::STAIRS: return sf::IntRect(336, 0,  16, 16); // (21,0)
    }
    return sf::IntRect(128, 48, 16, 16);
}

void Tile::draw(sf::RenderWindow& window, int x, int y)
{
    if (!explored) return;

    sf::Texture& tex = TextureManager::instance().get("assets/tilemap.png");

    sf::Sprite sprite(tex, rectFor(type));
    sprite.setScale(2.f, 2.f);
    sprite.setPosition(x * 32.f, y * 32.f);

    // visible → tam renk | explored+karanlık → soluk
    sprite.setColor(visible ? sf::Color(255, 255, 255) : sf::Color(60, 60, 60));

    window.draw(sprite);
}
