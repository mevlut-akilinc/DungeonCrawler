#include "Player.h"
#include "Dagger.h"
#include "HealthPotion.h"

Player::Player(int x, int y) : Entity(60, 12, 5, x, y, 1), maxHp(60)
{
    inventory.addItem(new Dagger());
    inventory.addItem(new HealthPotion());
}

void Player::reset()
{
    // Önce equipped pointer'ı temizle, sonra inventory'i sil (sırası önemli)
    equippedWeapon = nullptr;
    inventory.clear();

    // Stat'lar varsayılana
    Entity::setHp(maxHp);
    setAttack(12);
    setDefense(5);

    // Başlangıç eşyaları (constructor ile aynı)
    inventory.addItem(new Dagger());
    inventory.addItem(new HealthPotion());
}
