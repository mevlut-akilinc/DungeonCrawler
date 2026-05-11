#pragma once
#include <string>
#include  "Weapon.h"

class Dagger : public Weapon
{
    private:
    public:
    Dagger(): Weapon("Dagger", 8) {

    }

    void use(Player& Player) override {

    }

};

