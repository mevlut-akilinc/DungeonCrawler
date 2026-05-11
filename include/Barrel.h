#pragma once
#include "GameObject.h"



class Barrel : public GameObject //Miras alma islemi
    {

        public:
        Barrel(int x, int y) : GameObject(x, y , false){

        }

        void draw(sf::RenderWindow &window) override
        {
        }
    };
