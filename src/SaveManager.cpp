#include "SaveManager.h"
#include <fstream>
#include <iostream>

void SaveManager::save(Player& player, int floor)
{
    std::ofstream file("savegame.txt");
    if (!file.is_open())
    {
        std::cout << "Kayit dosyasi acilamadi!\n";
        return;
    }

    file << player.getHp()      << "\n";
    file << player.getAttack()  << "\n";
    file << player.getDefense() << "\n";
    file << floor               << "\n";

    // Envanter isimlerini kaydet
    const auto& items = player.getInventory().getItems();
    file << items.size() << "\n";
    for (const auto* item : items)
        file << item->getName() << "\n";

    std::cout << "Oyun kaydedildi. (Kat: " << floor << ")\n";
}

bool SaveManager::load(Player& player, int& floor)
{
    std::ifstream file("savegame.txt");
    if (!file.is_open()) return false;

    int hp, attack, defense, itemCount;
    file >> hp >> attack >> defense >> floor >> itemCount;

    player.setHp(hp);
    player.setAttack(attack);
    player.setDefense(defense);

    // Envanter isimlerini oku (item nesnesi yeniden yaratılmıyor — sadece bilgi)
    for (int i = 0; i < itemCount; i++)
    {
        std::string name;
        file >> name;
        std::cout << "  Yuklenen esya: " << name << "\n";
    }

    std::cout << "Kayit yuklendi. (Kat: " << floor << ")\n";
    return true;
}
