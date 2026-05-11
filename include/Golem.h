#pragma once
#include "Enemy.h"

class Golem : public Enemy
{

public:
    Golem(int x, int y) : Enemy(60, 12, 3, 1, x, y) {}

    void draw(sf::RenderWindow &window) override
    {
        // Çizim Kodu
    }

    void updateAI() override
    {
    }
};
