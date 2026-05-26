#pragma once
#include <string>
#include "Player.h"
#include "EnemyManager.h"

class SaveManager
{
public:
    // currentFloor + seed + player durumu + düşman listesi → dosyaya yazar
    static bool save(const std::string& path, Player& player,
                     unsigned int mapSeed, int currentFloor,
                     const EnemyManager& em);

    // Dosyadan okur; mapSeed ve currentFloor'u doldurur, enemyManager'ı sıfırlayıp yeniden yükler
    // Haritayı üretmek caller'ın sorumluluğu: srand(mapSeed); generator.generate()
    static bool load(const std::string& path, Player& player,
                     unsigned int& mapSeed, int& currentFloor,
                     EnemyManager& em);
};
