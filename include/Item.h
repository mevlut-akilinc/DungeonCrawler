#pragma once
#include <string>

class Player; // Forward Declaration
class Item
{
private:
    std::string name;

public:
    Item(std::string name) : name(name) {}
    virtual ~Item() = default;

    std::string getName() const { return name; }
    virtual void use(Player &player) = 0;

    // Silah / zırh gibi kuşanılabilir eşyalar true döndürür
    virtual bool isEquippable()          const { return false; }
    // Kuşanma / çıkarma — varsayılan: hiçbir şey yapmaz
    virtual void equip(Player& /*player*/)   {}
    virtual void unequip(Player& /*player*/) {}
};
