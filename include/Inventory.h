#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Item.h"

class Player;

class Inventory
{
private:
    std::vector<Item*> items;
    int maxSize;

public:
    Inventory(int maxSize = 10) : maxSize(maxSize) {}

    bool isFull() const { return (int)items.size() >= maxSize; }
    int  size()   const { return (int)items.size(); }

    const std::vector<Item*>& getItems() const { return items; }

    bool addItem(Item* item)
    {
        if (isFull()) return false;
        items.push_back(item);
        return true;
    }

    // Döndürdüğü string addMsg'ye geçilir; boşsa mesaj yok
    // Gövde src/Inventory.cpp'de — Player'ın tam tanımını oradan alır
    std::string useItem(int index, Player& player);

    void removeItem(int index)
    {
        if (index < 0 || index >= (int)items.size()) return;
        delete items[index];
        items.erase(items.begin() + index);
    }

    void clear()
    {
        for (Item* item : items) delete item;
        items.clear();
    }

    void display() const
    {
        if (items.empty()) { std::cout << "  (bos)\n"; return; }
        for (int i = 0; i < (int)items.size(); i++)
            std::cout << "  [" << i << "] " << items[i]->getName() << "\n";
    }

    ~Inventory()
    {
        for (Item* item : items) delete item;
    }
};
