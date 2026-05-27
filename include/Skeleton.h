#pragma once
#include "Enemy.h"
#include "Map.h"
#include "TextureManager.h"

class Skeleton : public Enemy
{
public:
    Skeleton(int x, int y) : Enemy(10, 5, 2, 6, x, y) {}
    int         getTypeId() const override { return 1; }
    std::string getName()   const override { return "Iskelet"; }

    void draw(sf::RenderWindow& window) override
    {
        sf::Sprite sprite(TextureManager::instance().get("assets/tilemap.png"),
                          sf::IntRect(400, 96, 16, 16)); // (25,6) humanoid iskelet
        sprite.setScale(2.f, 2.f);
        sprite.setPosition(x * 32.f, y * 32.f);
        window.draw(sprite);
        drawHitFlashOverlay(window);
    }

    void updateAI() override
    {
        if (!map) return;

        int newX = x;
        int newY = y;
        int dx = playerX - x;
        int dy = playerY - y;

        // Skeleton önce y ekseninde yaklaşır (Goblin'den farklı hareket deseni)
        if (dy != 0)
            newY += (dy > 0) ? 1 : -1;
        else if (dx != 0)
            newX += (dx > 0) ? 1 : -1;

        if (map->getTile(newX, newY).isWalkable())
        {
            x = newX;
            y = newY;
        }
    }
};
