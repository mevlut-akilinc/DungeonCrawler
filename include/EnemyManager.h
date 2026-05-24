#pragma once
#include <vector>
#include "Enemy.h"
#include "Map.h"

class EnemyManager {
private:
    std::vector<Enemy*> enemies;
public:
    void addEnemy(Enemy* enemy);

    // Her tur: oyuncu konumunu ve haritayı al, tüm düşmanları güncelle
    void updateAll(int playerX, int playerY, Map* map);

    // FoV kontrolü dahil: sadece görünür düşmanları çiz
    void drawAll(sf::RenderWindow& window, Map* map);

    void removeDeadEnemies();

    ~EnemyManager();
};
