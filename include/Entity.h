#pragma once
#include <SFML/Graphics.hpp> //Aı destekli yazılmıstır.

class Entity
{
private:
    int hp;     // Can
    int attack; // Attack puanı
    int defense;
protected:
    int x; // Position
    int y; // Position
    int speed;

public:
    Entity(int hp, int attack, int defense, int x, int y, int speed); // Constructor yazıldı.
    void takeDamage(int dmg);
    int getX() const { return x; }
    int getY() const { return y; }
    int getHp()      const { return hp; }
    int getAttack()  const { return attack; }
    int getDefense() const { return defense; }
    bool isAlive()   const { return hp > 0; }

    void setHp(int v)      { hp      = (v > 0 ? v : 0); }
    void setAttack(int v)  { attack  = v; }
    void setDefense(int v) { defense = v; }
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};
