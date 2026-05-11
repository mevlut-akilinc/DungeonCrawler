#pragma once
#include "Item.h"



class Potion : public Item
{
    private:
    int amount;

    public:
    Potion(std::string name ,int amount): Item (name){} //Constructor oluşturma islemi
    virtual  void use(Player& Player)= 0;

};
