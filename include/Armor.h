#pragma once
#include "Item.h"
#include "Player.h"

class Armor : public Item
{
private:
    int defenseBonus;

public:
    Armor() : Item("Armor"), defenseBonus(4) {}
    void use(Player& player) override
    {
        player.setDefense(player.getDefense() + defenseBonus);
    }
};
