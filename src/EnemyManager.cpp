#include "EnemyManager.h"
#include <cmath>

void EnemyManager::addEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}

int EnemyManager::updateAll(int playerX, int playerY, Map* map)
{
    int totalDamage = 0;
    for (Enemy* e : enemies)
    {
        e->setContext(playerX, playerY, map);

        // Komşuysa saldır, değilse hareket et
        int dx = std::abs(playerX - e->getX());
        int dy = std::abs(playerY - e->getY());
        if ((dx + dy) == 1)
            totalDamage += e->calculateAttackDamage();
        else
            e->update();
    }
    return totalDamage;
}

void EnemyManager::drawAll(sf::RenderWindow& window, Map* map)
{
    for (Enemy* e : enemies)
    {
        // Sadece oyuncunun görebildiği tile'daki düşmanları çiz
        if (map->getTile(e->getX(), e->getY()).isVisible())
            e->draw(window);
    }
}

void EnemyManager::removeDeadEnemies()
{
    for (auto it = enemies.begin(); it != enemies.end(); )
    {
        if (!(*it)->isAlive())
        {
            delete *it;
            it = enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void EnemyManager::clear()
{
    for (Enemy* e : enemies) delete e;
    enemies.clear();
}

Enemy* EnemyManager::getEnemyAt(int x, int y)
{
    for (Enemy* e : enemies)
        if (e->isAlive() && e->getX() == x && e->getY() == y)
            return e;
    return nullptr;
}

EnemyManager::~EnemyManager()
{
    clear();
}
