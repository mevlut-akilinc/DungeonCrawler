#include "Player.h"
#include "Dagger.h"
#include "HealthPotion.h"

Player::Player(int x, int y) : Entity(60, 12, 5, x, y, 1), maxHp(60)
{
    inventory.addItem(new Dagger());
    inventory.addItem(new HealthPotion());
}
