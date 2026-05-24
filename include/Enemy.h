#pragma once
#include "Entity.h"
class Map; // Enemy harita bilgisine pointer üzerinden erişir

class Enemy : public Entity
{
protected:
    int playerX = 0; // AI'nin hedef koordinatları (EnemyManager tarafından set edilir)
    int playerY = 0;
    Map* map = nullptr;

public:
    Enemy(int hp, int attack, int defense, int speed, int x, int y);

    // EnemyManager her tur önce bu fonksiyonu çağırır, sonra update() çağırır
    void setContext(int px, int py, Map* m);

    // Alt sınıflar kendi AI davranışını burada tanımlar
    virtual void updateAI() = 0;

    void update() override
    {
        updateAI();
    }
};
