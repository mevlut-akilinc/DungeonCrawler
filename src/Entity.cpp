#include "Entity.h"

Entity::Entity(int hp, int attack, int defense, int x, int y, int speed)
{
    this->hp = hp;
    this->attack = attack;
    this->defense = defense;
    this->x = x;
    this->y = y;
    this->speed = speed;
}

void Entity::takeDamage(int dmg)
{
    hp -= dmg;
    if (hp < 0) hp = 0;
}
