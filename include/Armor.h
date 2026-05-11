#pragma once
#include "Item.h"
#include <iostream>


class Armor : public Item
{
    private:
    int defencebonus = 4;

    public:
    Armor() : Item("Armor"){}
    void use(Player& Player) override{

    }

};
