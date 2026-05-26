#include "InputHandler.h"
#include "GameConstants.h"
#include "Chest.h"

using namespace GameConstants;

namespace {
    // 1-5 tuşları (Num1..Num5)
    const sf::Keyboard::Key NUM_KEYS[HOTBAR_SLOTS] = {
        sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3,
        sf::Keyboard::Num4, sf::Keyboard::Num5
    };
}

bool InputHandler::processHeldKeys(Player& player, Map& map, MsgCallback addMsg)
{
    bool dropped = false;

    // Hangi numara tuşuna basılı (yoksa -1)
    int numIdx = -1;
    for (int i = 0; i < HOTBAR_SLOTS; i++)
        if (sf::Keyboard::isKeyPressed(NUM_KEYS[i])) { numIdx = i; break; }

    bool cNow = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
    bool eNow = sf::Keyboard::isKeyPressed(sf::Keyboard::E);

    // --- E: sandık aç (sadece edge'de) ---
    if (eNow && !actionKeyWasPressed_)
    {
        Chest* chest = map.getChestAt(player.getX(), player.getY());
        if (chest) chest->open(player, addMsg);
        else       addMsg("Burada sandik yok.");
    }

    // --- C + 1-5: yere bırak (use'tan ÖNCE kontrol edilir; öncelik C'dedir) ---
    if (cNow && numIdx >= 0 && !actionKeyWasPressed_)
    {
        auto& inv = player.getInventory();
        if (numIdx < inv.size())
        {
            // Kuşanılmışsa önce silahı çıkar
            if (player.getEquippedWeapon() == inv.getItems()[numIdx])
                player.setEquippedWeapon(nullptr);

            Item* item = inv.takeItem(numIdx);
            if (item)
            {
                map.placeItem(player.getX(), player.getY(), item);
                addMsg(item->getName() + " yere birakildi.");
                dropped = true;
            }
        }
        else
            addMsg("Slot " + std::to_string(numIdx + 1) + " bos.");
    }
    // --- 1-5: kullan (sadece C basılı DEĞİLSE — C+1 hem use hem drop tetiklemez) ---
    else if (!cNow && numIdx >= 0 && !actionKeyWasPressed_)
    {
        const auto& items = player.getInventory().getItems();
        if (numIdx < (int)items.size())
        {
            std::string result = player.getInventory().useItem(numIdx, player);
            if (!result.empty()) addMsg(result);
        }
        else
            addMsg("Slot " + std::to_string(numIdx + 1) + " bos.");
    }

    // Edge-detect state: bir sonraki frame için sakla
    actionKeyWasPressed_ = (numIdx >= 0) || eNow;

    // --- SPACE: envanteri mesaj kuyruğunda göster ---
    bool spaceNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    if (spaceNow && !spaceWasPressed_)
    {
        const auto& items = player.getInventory().getItems();
        if (items.empty())
            addMsg("Envanter bos.");
        else
        {
            addMsg("-- Envanter --");
            for (int i = 0; i < (int)items.size(); i++)
                addMsg("[" + std::to_string(i + 1) + "] " + items[i]->getName());
        }
    }
    spaceWasPressed_ = spaceNow;

    return dropped;
}
