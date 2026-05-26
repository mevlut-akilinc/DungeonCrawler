#pragma once
#include "Enemy.h"
#include "Map.h"

class Golem : public Enemy
{
    int turnCounter = 0; // Golem yavaş: her 2 turda bir hareket eder (speed=1)
public:
    Golem(int x, int y) : Enemy(60, 9, 3, 1, x, y) {}
    int         getTypeId() const override { return 2; }
    std::string getName()   const override { return "Golem"; }

    void draw(sf::RenderWindow& window) override
    {
        sf::RectangleShape shape(sf::Vector2f(32.f, 32.f));
        shape.setFillColor(sf::Color(120, 60, 180)); // Mor
        shape.setPosition(x * 32.f, y * 32.f);
        window.draw(shape);
    }

    void updateAI() override
    {
        if (!map) return;

        // Golem ağır: sadece çift turda hareket eder
        if (++turnCounter % 2 != 0) return;

        int newX = x;
        int newY = y;
        int dx = playerX - x;
        int dy = playerY - y;

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
