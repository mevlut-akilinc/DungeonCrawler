#pragma once
#include "Enemy.h"

class Skeleton : public Enemy
{

public:
    Skeleton(int x, int y) : Enemy(10, 5, 2, 6, x, y) {}

    void draw(sf::RenderWindow &window) override
    {
        // Çizim Kodu
    }

    void updateAI() override
    {
    }
};
