#pragma once
#include "Entity.h"

class Enemy : public Entity
{

public:
    Enemy(int hp, int attack, int defense, int speed, int x, int y);
    // Benim anladığım Enemy' i clasını miras alacak her sınıf UpdateAI() methodunu kullanabilir ama Enemy clasının kendisi bu methoda sahip değil çünkü sahip olucak bir yapıda değil..
    virtual void updateAI() = 0;

    void update() override
    {
        updateAI();
    }
};
