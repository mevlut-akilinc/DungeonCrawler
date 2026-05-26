#pragma once
#include "Entity.h"
#include <functional>
#include <string>
class Map;

class Enemy : public Entity
{
protected:
    int playerX = 0;
    int playerY = 0;
    Map* map = nullptr;

    // Düşman oyuncuya komşu mu? (Manhattan mesafe == 1)
    bool isAdjacentToPlayer() const
    {
        int dx = std::abs(playerX - x);
        int dy = std::abs(playerY - y);
        return (dx + dy) == 1;
    }

public:
    Enemy(int hp, int attack, int defense, int speed, int x, int y);

    void setContext(int px, int py, Map* m);

    virtual void        updateAI()  = 0;
    virtual int         getTypeId() const = 0;
    virtual std::string getName()   const = 0;

    // Düşman saldırı sonucu: hasar değeri döndürür (main.cpp bunu player'a uygular)
    int calculateAttackDamage() const { return getAttack(); }

    void update() override { updateAI(); }
};
