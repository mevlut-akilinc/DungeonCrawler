#pragma once
#include "Item.h"
#include "Chest.h"

#include <vector>

class NormalChest : public Chest // Miras alma islemi
{

public:
    NormalChest(int x, int y) : Chest(x, y)
    {
    }
    void open(Player &player) override
    {
    }
    void draw(sf::RenderWindow &window) override {}
};
