#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
private:
    int x;
    int y;
    bool walkable;

public:
    GameObject(int x, int y, bool walkable);

    virtual void draw(sf::RenderWindow &window) = 0; // Saf sanal GameObject çizilmiyor varil felan çiziliyor.

    int getX() const;
    int getY() const;
    bool isWalkable() const { return walkable; }
};
