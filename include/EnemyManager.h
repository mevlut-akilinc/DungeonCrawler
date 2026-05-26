#pragma once
#include <vector>
#include <functional>
#include <string>
#include "Enemy.h"
#include "Map.h"

class Player;

class EnemyManager
{
private:
    std::vector<Enemy *> enemies;

public:
    void addEnemy(Enemy *enemy);

    // Komşu olmayanları hareket ettirir, komşu olanlar yerinde durur (saldırı fazı ayrı)
    void updateAll(int playerX, int playerY, Map *map);

    // Komşu her düşman için savunmaya göre ayrı ayrı hasar uygular; toplam net hasarı döndürür
    int attackPlayer(Player &player,
                     std::function<void(const std::string &)> addMsg);

    // FoV kontrolü dahil: sadece görünür düşmanları çiz
    void drawAll(sf::RenderWindow &window, Map *map);

    void removeDeadEnemies();
    void clear(); // Yeni kat geçişinde tüm düşmanları sil

    // Verilen koordinatta düşman varsa pointer döndür, yoksa nullptr
    Enemy *getEnemyAt(int x, int y);

    const std::vector<Enemy *> &getEnemies() const { return enemies; }

    ~EnemyManager();
};
