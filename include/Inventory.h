#pragma once
#include <string>
#include <vector>
#include "Item.h"

class Player;

class Inventory
{
private:
    std::vector<Item *> items;
    int maxSize;

public:
    void addItem(Item *item)
    {
    }

    void useItem(int index, Player &player)
    {
    }

    void removeItem(int index)
    {
    }

    void display()
    {
    }
};

// Ai destekli yazıldı buradaki kodlar daha ayrıntılı üzerinde çalışılsın.
