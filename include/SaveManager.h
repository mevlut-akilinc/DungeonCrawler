#pragma once
#include "Player.h"

class SaveManager
{
public:
    void save(Player &player, int floor);
    bool load(Player &player, int &floor);
};
