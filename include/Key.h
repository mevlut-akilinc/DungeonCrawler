#pragma once
#include "Item.h"

class Key : public Item
{
private:
public:
    Key() : Item("Key") {} // Constructor oluşturma islemi
    void use(Player &Player)
    {
    }
};
