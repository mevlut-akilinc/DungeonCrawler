#include "EnemyManager.h"

void EnemyManager::addEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}

void EnemyManager::updateAll(int playerX, int playerY, Map* map)
{
    for (Enemy* e : enemies)
    {
        e->setContext(playerX, playerY, map);
        e->update();
    }
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

EnemyManager::~EnemyManager()
{
    for (Enemy* e : enemies)
        delete e;
    enemies.clear();
}
