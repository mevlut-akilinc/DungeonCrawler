#include "GameObject.h"

GameObject::GameObject(int x, int y, bool walkable)
    : x(x), y(y), walkable(walkable)
{
}

int GameObject::getX() const { return x; }
int GameObject::getY() const { return y; }
