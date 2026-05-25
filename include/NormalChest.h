#pragma once
#include "Chest.h"
#include "Player.h"
#include "HealthPotion.h"
#include "Sword.h"
#include "Armor.h"
#include <functional>
#include <string>
#include <cstdlib>

class NormalChest : public Chest
{
private:
    bool opened;

public:
    NormalChest(int x, int y) : Chest(x, y), opened(false) {}

    void open(Player& player, std::function<void(const std::string&)> addMsg) override
    {
        if (opened) { addMsg("Sandik zaten acik."); return; }
        opened = true;

        int roll = rand() % 3;
        Item* item = nullptr;
        if      (roll == 0) item = new HealthPotion();
        else if (roll == 1) item = new Sword();
        else                item = new Armor();

        if (player.getInventory().addItem(item))
            addMsg("Sandiktan " + item->getName() + " bulundu!");
        else
        {
            addMsg("Envanter dolu, " + item->getName() + " alinamadi.");
            delete item;
        }
    }

    void draw(sf::RenderWindow& window) override
    {
        sf::RectangleShape shape(sf::Vector2f(28.f, 28.f));
        shape.setFillColor(opened ? sf::Color(80, 50, 20) : sf::Color(180, 120, 40));
        shape.setPosition(getX() * 32.f + 2.f, getY() * 32.f + 2.f);
        window.draw(shape);
    }

    bool isOpened() const { return opened; }
};
