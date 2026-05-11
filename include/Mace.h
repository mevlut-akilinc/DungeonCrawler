#pragma once
#include <string>
#include  "Weapon.h"

class Mace : public Weapon
{
    private:
    public:
    Mace(): Weapon("Mace", 25) {

    }

    void use(Player& Player) override {

    }

};

