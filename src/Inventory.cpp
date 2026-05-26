#include "Inventory.h"
#include "Player.h"   // Tam tanım burada — döngüsel bağımlılık kırılır

std::string Inventory::useItem(int index, Player& player)
{
    if (index < 0 || index >= (int)items.size()) return "";
    Item* item = items[index];

    if (item->isEquippable())
    {
        // --- WIELD YOLU: silah envanterden silinmez, sadece aktif işaretlenir ---
        if (player.getEquippedWeapon() == item)
            return item->getName() + " zaten kusanili.";

        // Önceki silahı çıkar (stat'ı geri al)
        if (player.getEquippedWeapon())
            player.getEquippedWeapon()->unequip(player);

        // Yeni silahı kuşan (stat'ı ekle)
        item->equip(player);
        player.setEquippedWeapon(item);
        return item->getName() + " kusanildi!";
    }

    // --- TÜKETİCİ YOLU: potion, key vb. — kullan ve envanterden sil ---
    item->use(player);
    std::string msg = item->getName() + " kullanildi!";
    removeItem(index);
    return msg;
}
