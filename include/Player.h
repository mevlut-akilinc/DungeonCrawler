#pragma once
#include "Entity.h"
#include "Map.h"

class Player : public Entity
{
public:
    Player(int x, int y) : Entity(50, 10, 3, x, y, 1) {}

    void handleInput(Map& map)
    {
        int newX = getX();
        int newY = getY();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) newY--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) newY++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) newX--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) newX++;

        if (map.getTile(newX, newY).isWalkable())
        {
            x = newX;
            y = newY;
        }
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
