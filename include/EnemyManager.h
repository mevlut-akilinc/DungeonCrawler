#pragma once
#include <vector>
#include "Enemy.h"
#include "Map.h"

class EnemyManager {
private:
    std::vector<Enemy*> enemies;
public:
    void addEnemy(Enemy* enemy);

    // Her tur: düşmanları güncelle, komşu düşmanların toplam saldırı hasarını döndür
    int updateAll(int playerX, int playerY, Map* map);

    // FoV kontrolü dahil: sadece görünür düşmanları çiz
    void drawAll(sf::RenderWindow& window, Map* map);

    void removeDeadEnemies();
    void clear();   // Yeni kat geçişinde tüm düşmanları sil

    // Verilen koordinatta düşman varsa pointer döndür, yoksa nullptr
    Enemy* getEnemyAt(int x, int y);

    ~EnemyManager();
};
