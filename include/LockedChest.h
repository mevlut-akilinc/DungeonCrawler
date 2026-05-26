#pragma once
#include "Chest.h"
#include "Player.h"
#include "Mace.h"
#include "ShieldPotion.h"
#include "TextureManager.h"
#include <functional>
#include <string>

class LockedChest : public Chest
{
private:
    bool opened;

    // Envanterde "Key" adlı eşya var mı? Varsa indexini döndür, yoksa -1
    int findKey(Player& player) const
    {
        const auto& items = player.getInventory().getItems();
        for (int i = 0; i < (int)items.size(); i++)
            if (items[i]->getName() == "Key") return i;
        return -1;
    }

public:
    LockedChest(int x, int y) : Chest(x, y), opened(false) {}

    void open(Player& player, std::function<void(const std::string&)> addMsg) override
    {
        if (opened) { addMsg("Sandik zaten acik."); return; }

        int keyIdx = findKey(player);
        if (keyIdx == -1)
        {
            addMsg("Kilitli sandik! Bir anahtar lazim.");
            return;
        }

        player.getInventory().removeItem(keyIdx);
        opened = true;
        addMsg("Anahtar kullanildi, kilitli sandik acildi!");

        Item* item = (rand() % 2 == 0) ? (Item*)new Mace() : (Item*)new ShieldPotion();
        if (player.getInventory().addItem(item))
            addMsg("Sandiktan " + item->getName() + " cikar!");
        else
        {
            addMsg("Envanter dolu!");
            delete item;
        }
    }

    void draw(sf::RenderWindow& window) override
    {
        sf::Sprite sprite(TextureManager::instance().get("assets/tilemap.png"),
                          sf::IntRect(144, 112, 16, 16)); // (9,7) kilitli sandık
        sprite.setScale(2.f, 2.f);
        sprite.setPosition(getX() * 32.f, getY() * 32.f);
        sprite.setColor(opened ? sf::Color(100, 100, 100) : sf::Color(180, 140, 255));
        window.draw(sprite);
    }
};
