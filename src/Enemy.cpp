#include "Enemy.h"

Enemy::Enemy(int hp, int attack, int defense, int speed, int x, int y)
    : Entity(hp, attack, defense, x, y, speed)
{
}

void Enemy::setContext(int px, int py, Map* m)
{
    playerX = px;
    playerY = py;
    map     = m;
}
