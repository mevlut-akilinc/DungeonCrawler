#pragma once
#include <SFML/Graphics.hpp> //Aı destekli yazılmıstır.

class Entity
{
private:
    int hp;     // Can
    int attack; // Attack puanı
    int defense;
    int x; // Position
    int y; // Position
    int speed;

public:
    Entity(int hp, int attack, int defense, int x, int y, int speed); // Constructor yazıldı.
    void takeDamage(int dmg);                                         // Kac hasar aldıgı
    virtual void update() = 0;                                        // Hareket dinamiği
    virtual void draw(sf::RenderWindow &window) = 0;
};
