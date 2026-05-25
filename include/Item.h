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
};
