#pragma once
#include <string>

class Player; // Forward Declaration
class Item
{
private:
    std::string name;





public:

    //Constructor
    Item(std:: string name){} // tipini parantez içinde belirtmen lazım
    virtual void use (Player& Player) = 0;


};
