#pragma once
#include "Enemy.h"
#include "Map.h"

class Goblin : public Enemy
{
public:
    Goblin(int x, int y) : Enemy(30, 8, 5, 4, x, y) {}

    void draw(sf::RenderWindow& window) override
    {
        sf::RectangleShape shape(sf::Vector2f(32.f, 32.f));
        shape.setFillColor(sf::Color(0, 180, 0)); // Yeşil
        shape.setPosition(x * 32.f, y * 32.f);
        window.draw(shape);
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
