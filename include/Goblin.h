#pragma once
#include "Enemy.h"
#include "Map.h"
#include "TextureManager.h"

class Goblin : public Enemy
{
public:
    Goblin(int x, int y) : Enemy(30, 8, 5, 4, x, y) {}
    int         getTypeId() const override { return 0; }
    std::string getName()   const override { return "Goblin"; }

    void draw(sf::RenderWindow& window) override
    {
        sf::Sprite sprite(TextureManager::instance().get("assets/tilemap.png"),
                          sf::IntRect(320, 144, 16, 16)); // (20,9) yeşil boynuzlu goblin
        sprite.setScale(2.f, 2.f);
        sprite.setPosition(x * 32.f, y * 32.f);
        window.draw(sprite);
    }

    void updateAI() override
    {
        if (!map) return;

        int newX = x;
        int newY = y;
        int dx = playerX - x;
        int dy = playerY - y;

        // Manhattan hareketi: x farkı varsa x'te, yoksa y'de bir adım at
        if (dx != 0)
            newX += (dx > 0) ? 1 : -1;
        else if (dy != 0)
            newY += (dy > 0) ? 1 : -1;

        if (map->getTile(newX, newY).isWalkable())
        {
            x = newX;
            y = newY;
        }
    }
};
