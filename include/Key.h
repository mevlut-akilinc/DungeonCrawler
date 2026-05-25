#pragma once
#include "Item.h"
#include <iostream>

class Key : public Item
{
public:
    Key() : Item("Key") {}
    void use(Player& player) override
    {
        std::cout << "Anahtar kilidi sandiklarda kullanilir, kendiliğinden kullanilamaz.\n";
    }
};
