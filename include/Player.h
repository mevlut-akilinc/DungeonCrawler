#pragma once
#include "Entity.h"

class Player : public Entity
{

public:
    Player(int x, int y) : Entity(50, 10, 3, 3, x, y) {} // i constructor'ın süslü parantezine girmeden önce, üst sınıfın constructor'ını çağırıyorsun

    void handleInput()
    {
    }

    void draw(sf::RenderWindow &window) override
    {
        // Çizim Kodu
    }

    void update() override
    {
    }
};
