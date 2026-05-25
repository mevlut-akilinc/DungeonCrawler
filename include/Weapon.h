#pragma once
#include "Item.h"
#include "Player.h"

class Weapon : public Item
{
private:
    int damage;

public:
    Weapon(std::string name, int damage) : Item(name), damage(damage) {}

    void use(Player& player) override
    {
        player.setAttack(player.getAttack() + damage);
    }

protected:
    int getDamage() const { return damage; }
};
