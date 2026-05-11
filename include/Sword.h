#pragma once
#include <string>
#include  "Weapon.h"

class Sword : public Weapon
{
    private:
    public:
    Sword(): Weapon("Sword", 15) {
        
    }

    void use(Player& Player) override {

    }

};

