#pragma once
#include "Chest.h"
#include "Player.h"
#include "HealthPotion.h"
#include "Sword.h"
#include "Armor.h"
#include "TextureManager.h"
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
        // Açıksa (8,7), kapalıysa (8,7) — renk tonu ile ayırt
        sf::Sprite sprite(TextureManager::instance().get("assets/tilemap.png"),
                          sf::IntRect(128, 112, 16, 16)); // (8,7) normal sandık
        sprite.setScale(2.f, 2.f);
        sprite.setPosition(getX() * 32.f, getY() * 32.f);
        sprite.setColor(opened ? sf::Color(120, 80, 50) : sf::Color::White);
        window.draw(sprite);
    }

    bool isOpened() const { return opened; }
};
