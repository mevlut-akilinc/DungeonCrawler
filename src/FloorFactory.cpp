#include "FloorFactory.h"
#include "GameConstants.h"
#include "HealthPotion.h"
#include "Key.h"
#include "NormalChest.h"
#include "LockedChest.h"
#include "Goblin.h"
#include "Skeleton.h"
#include "Golem.h"

using namespace GameConstants;

FloorFactory::FloorFactory(MapGenerator& gen, EnemyManager& em)
    : generator_(gen), em_(em)
{
}

Map* FloorFactory::buildLayout()
{
    Map* map = generator_.generate(MAP_WIDTH, MAP_HEIGHT);
    const auto& rooms = generator_.getRooms();

    // İlk odaya her zaman bir HealthPotion bırak
    if (!rooms.empty())
    {
        int cx = rooms[0].left + rooms[0].width  / 2;
        int cy = rooms[0].top  + rooms[0].height / 2;
        map->placeItem(cx, cy, new HealthPotion());
    }

    for (size_t i = 1; i < rooms.size(); i++)
    {
        int cx = rooms[i].left + rooms[i].width  / 2;
        int cy = rooms[i].top  + rooms[i].height / 2;

        // Köşeye sandık (her 3. odaya normal, 5. odaya kilitli)
        int chestX = rooms[i].left + 1;
        int chestY = rooms[i].top  + 1;
        if (map->getTile(chestX, chestY).getType() == TileType::FLOOR)
        {
            if      (i % 5 == 0) map->addChest(new LockedChest(chestX, chestY));
            else if (i % 3 == 0) map->addChest(new NormalChest(chestX, chestY));
        }

        // Her 4. odaya anahtar
        if (i % 4 == 0) map->placeItem(cx - 1, cy, new Key());

        // Her çift odaya HealthPotion
        if (i % 2 == 0) map->placeItem(cx + 1, cy, new HealthPotion());
    }

    return map;
}

Map* FloorFactory::generateFloor(int currentFloor)
{
    em_.clear();
    Map* map = buildLayout();
    const auto& rooms = generator_.getRooms();

    for (size_t i = 1; i < rooms.size(); i++)
    {
        // Kat 1: yarı yoğunluk (her iki odadan biri boş)
        if (currentFloor == 1 && i % 2 == 0) continue;

        int cx = rooms[i].left + rooms[i].width  / 2;
        int cy = rooms[i].top  + rooms[i].height / 2;

        if (currentFloor == 1)
        {
            // Kat 1: sadece Goblin ve Iskelet
            if (i % 2 == 1) em_.addEnemy(new Goblin(cx, cy));
            else            em_.addEnemy(new Skeleton(cx, cy));
        }
        else
        {
            // Kat 2+: Golem dahil tüm odalar dolu
            if      (i % 3 == 0) em_.addEnemy(new Golem(cx, cy));
            else if (i % 3 == 1) em_.addEnemy(new Goblin(cx, cy));
            else                 em_.addEnemy(new Skeleton(cx, cy));
        }
    }

    return map;
}

void FloorFactory::spawnPlayer(Player& player, Map& map)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
            if (map.getTile(x, y).getType() == TileType::FLOOR)
            {
                player.teleport(x, y);
                return;
            }
}
