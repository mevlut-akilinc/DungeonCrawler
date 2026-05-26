#include "EnemyManager.h"
#include "Player.h"
#include <cmath>
#include <algorithm>

void EnemyManager::addEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}

void EnemyManager::updateAll(int playerX, int playerY, Map* map)
{
    for (Enemy* e : enemies)
    {
        e->setContext(playerX, playerY, map);

        int dx = std::abs(playerX - e->getX());
        int dy = std::abs(playerY - e->getY());
        if ((dx + dy) != 1)  // komşu değilse hareket et
            e->update();
        // komşuysa yerinde dur — saldırı attackPlayer'da
    }
}

int EnemyManager::attackPlayer(Player& player,
                               std::function<void(const std::string&)> addMsg)
{
    int totalNet = 0;
    for (Enemy* e : enemies)
    {
        int dx = std::abs(player.getX() - e->getX());
        int dy = std::abs(player.getY() - e->getY());
        if ((dx + dy) != 1) continue;

        int raw = e->calculateAttackDamage();
        int net = std::max(1, raw - player.getDefense());
        player.setHp(player.getHp() - net);
        addMsg(e->getName() + " sana " + std::to_string(net) + " hasar verdi!");
        totalNet += net;
    }
    return totalNet;
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
