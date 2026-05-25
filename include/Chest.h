#pragma once
#include "Item.h"
#include "GameObject.h"
#include <vector>
#include <functional>
#include <string>

class Player;
class Chest : public GameObject
{
public:
    Chest(int x, int y) : GameObject(x, y, false) {}

    // addMsg: mesajı ekrana iletmek için callback
    virtual void open(Player& player, std::function<void(const std::string&)> addMsg) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};
