#include "SaveManager.h"
#include "HealthPotion.h"
#include "ShieldPotion.h"
#include "Sword.h"
#include "Dagger.h"
#include "Mace.h"
#include "Armor.h"
#include "Key.h"
#include "Goblin.h"
#include "Skeleton.h"
#include "Golem.h"
#include <fstream>

// Kayıt formatı (text):
//   seed floor
//   player_x player_y hp attack defense
//   item_count
//   ItemName   (her biri ayrı satır)
//   ...
//   enemy_count
//   typeId x y hp   (her biri ayrı satır)
//   ...

static Item* createItemByName(const std::string& name)
{
    if (name == "HealthPotion") return new HealthPotion();
    if (name == "ShieldPotion") return new ShieldPotion();
    if (name == "Sword")        return new Sword();
    if (name == "Dagger")       return new Dagger();
    if (name == "Mace")         return new Mace();
    if (name == "Armor")        return new Armor();
    if (name == "Key")          return new Key();
    return nullptr;
}

static Enemy* createEnemyById(int typeId, int x, int y)
{
    if (typeId == 0) return new Goblin(x, y);
    if (typeId == 1) return new Skeleton(x, y);
    if (typeId == 2) return new Golem(x, y);
    return nullptr;
}

bool SaveManager::save(const std::string& path, Player& player,
                       unsigned int mapSeed, int currentFloor,
                       const EnemyManager& em)
{
    std::ofstream f(path);
    if (!f.is_open()) return false;

    f << mapSeed << " " << currentFloor << "\n";
    f << player.getX() << " " << player.getY() << " "
      << player.getHp() << " " << player.getAttack() << " "
      << player.getDefense() << "\n";

    const auto& items = player.getInventory().getItems();
    f << items.size() << "\n";
    for (const Item* item : items)
        f << item->getName() << "\n";

    const auto& enemies = em.getEnemies();
    f << enemies.size() << "\n";
    for (const Enemy* e : enemies)
        f << e->getTypeId() << " " << e->getX() << " " << e->getY() << " " << e->getHp() << "\n";

    return true;
}

bool SaveManager::load(const std::string& path, Player& player,
                       unsigned int& mapSeed, int& currentFloor,
                       EnemyManager& em)
{
    std::ifstream f(path);
    if (!f.is_open()) return false;

    f >> mapSeed >> currentFloor;

    int px, py, hp, atk, def;
    f >> px >> py >> hp >> atk >> def;

    player.teleport(px, py);
    player.setHp(hp);
    player.setAttack(atk);
    player.setDefense(def);

    player.getInventory().clear();
    int itemCount;
    f >> itemCount;
    f.ignore();
    for (int i = 0; i < itemCount; i++)
    {
        std::string name;
        std::getline(f, name);
        Item* item = createItemByName(name);
        if (item) player.getInventory().addItem(item);
    }

    em.clear();
    int enemyCount;
    f >> enemyCount;
    for (int i = 0; i < enemyCount; i++)
    {
        int typeId, ex, ey, ehp;
        f >> typeId >> ex >> ey >> ehp;
        Enemy* e = createEnemyById(typeId, ex, ey);
        if (e)
        {
            e->setHp(ehp);
            em.addEnemy(e);
        }
    }

    return true;
}
