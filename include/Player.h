#pragma once
#include "Entity.h"
#include "Map.h"
#include "Inventory.h"
#include "EnemyManager.h"
#include <functional>
#include <string>
#include <algorithm>

class Player : public Entity
{
private:
    Inventory inventory;
    int maxHp;

public:
    Player(int x, int y) : Entity(50, 10, 3, x, y, 1), maxHp(50) {}

    Inventory& getInventory() { return inventory; }
    int getMaxHp() const { return maxHp; }

    // WASD: hareket veya bump-to-attack. addMsg ile mesaj gönderir.
    // true döner → düşman turu tetiklenir
    bool handleInput(Map& map, EnemyManager& em,
                     std::function<void(const std::string&)> addMsg)
    {
        int newX = getX();
        int newY = getY();

        bool keyPressed = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { newY--; keyPressed = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { newY++; keyPressed = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { newX--; keyPressed = true; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { newX++; keyPressed = true; }

        if (!keyPressed) return false;

        // Hedef karede düşman var mı?
        Enemy* target = em.getEnemyAt(newX, newY);
        if (target)
        {
            int dmg = std::max(1, getAttack() - target->getDefense());
            target->takeDamage(dmg);
            addMsg(target->isAlive()
                ? "Dusmana " + std::to_string(dmg) + " hasar verdin!"
                : "Dusmaní yok ettin!");
            return true; // saldırı da bir tur harcar
        }

        if (map.getTile(newX, newY).isWalkable())
        {
            x = newX;
            y = newY;
        }

        return true;
    }

    void teleport(int newX, int newY) { x = newX; y = newY; }

    // Oyuncunun üzerinde durduğu tile STAIRS mi?
    bool isOnStairs(Map& map) const
    {
        return map.getTile(x, y).getType() == TileType::STAIRS;
    }

    // HP'yi maxHp ile sınırla
    void setHp(int v)
    {
        Entity::setHp(v > maxHp ? maxHp : v);
    }

    void draw(sf::RenderWindow& window) override
    {
        sf::RectangleShape shape(sf::Vector2f(32.f, 32.f));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(x * 32.f, y * 32.f);
        window.draw(shape);
    }

    void update() override {}
};
