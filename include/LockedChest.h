#pragma once
#include "Item.h"
#include "Chest.h"

#include <vector>

class LockedChest : public Chest // Miras alma islemi
{

public:
    LockedChest(int x, int y) : Chest(x, y)
    {
    }
    void open(Player &player) override
    {
    }
    void draw(sf::RenderWindow &window) override {}
};
