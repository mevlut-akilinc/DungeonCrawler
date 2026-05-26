#pragma once
#include "Item.h"
#include "Player.h"

class Weapon : public Item
{
private:
    int damage;

public:
    Weapon(std::string name, int damage) : Item(name), damage(damage) {}

    // Silahlar kuşanılabilir — 1-5 ile "wield" yoluna girer, tüketilmez
    bool isEquippable() const override { return true; }

    // Kuşanınca ATK artar, çıkarınca geri düşer
    void equip(Player& player)   override { player.setAttack(player.getAttack() + damage); }
    void unequip(Player& player) override { player.setAttack(player.getAttack() - damage); }

    // Artık doğrudan çağrılmıyor; wield mekanizması equip/unequip kullanır
    void use(Player& /*player*/) override {}

protected:
    int getDamage() const { return damage; }
};
