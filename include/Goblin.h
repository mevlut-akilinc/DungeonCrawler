#pragma once
#include "Enemy.h"

class Goblin : public Enemy
{

public:
    Goblin(int x ,int y): Enemy(30, 8 , 5, 4 , x, y){}

    void draw(sf::RenderWindow& window) override
    {
        //Çizim Kodu
    }

    void updateAI() override
    {

    }


};
