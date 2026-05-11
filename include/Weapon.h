#pragma once
#include "Item.h"
#include <iostream>
#include <string>  //Bunlar silinmeli ama silmeyeceğim çünkü ai kullanmadan bu projeyi yapıyorum ve bu noktada bu kütüphaneleri silmeyi unuttum ai bana sil dedi ama ben silmeyceğim çünkü kodları  copy paste yapmıyorum hocam


class Weapon : public Item
{
    private:
    int damage;


    public:
    Weapon(std::string name , int damage); // Constructor oluşturma islemi
    virtual void use(Player& Player) override{

    }
};
