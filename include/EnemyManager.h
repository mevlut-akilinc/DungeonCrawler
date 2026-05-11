#pragma once
#include <vector>
#include "Enemy.h"

class EnemyManager {
private:
    std::vector<Enemy*> enemies;
public:
    void addEnemy(Enemy* enemy);
    void updateAll();
    void drawAll(sf::RenderWindow& window);
    void removeDeadEnemies();
};
