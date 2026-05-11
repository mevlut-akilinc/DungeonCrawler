#pragma once
#include "Item.h"
#include "GameObject.h"
#include <vector>

class Player;
class Chest : public GameObject // Miras alma islemi
{
private:
    std::vector<Item *> contents;

public:
    Chest(int x, int y) : GameObject(x, y, false)
    {
    }
    virtual void open(Player &player) = 0; // Pointer ve referans kullanımları
    virtual void draw(sf::RenderWindow &window) = 0;
};
