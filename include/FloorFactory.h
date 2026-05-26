#pragma once
#include "Map.h"
#include "MapGenerator.h"
#include "EnemyManager.h"
#include "Player.h"

// Harita üretimi ve oyuncu yerleştirme tek bir sınıfta toplandı
class FloorFactory
{
public:
    FloorFactory(MapGenerator& gen, EnemyManager& em);

    // Sadece harita + sandık + yerde eşya (düşmansız)
    // Save load sırasında haritayı seed ile aynen yeniden üretmek için kullanılır
    Map* buildLayout();

    // buildLayout + kat seviyesine göre düşman yerleştirir
    Map* generateFloor(int currentFloor);

    // Haritadaki ilk FLOOR tile'ına oyuncuyu taşır
    static void spawnPlayer(Player& player, Map& map);

private:
    MapGenerator& generator_;
    EnemyManager& em_;
};
