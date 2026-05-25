#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "MapGenerator.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Goblin.h"
#include "Skeleton.h"
#include "Golem.h"
#include "NormalChest.h"
#include "LockedChest.h"
#include "Key.h"

// Yeni bir kat üret, düşmanları ve eşyaları yerleştir
Map* generateFloor(MapGenerator& generator, EnemyManager& enemyManager)
{
    enemyManager.clear();
    Map* map = generator.generate(80, 50);

    const auto& rooms = generator.getRooms();

    for (size_t i = 1; i < rooms.size(); i++)
    {
        int cx = rooms[i].left + rooms[i].width  / 2;
        int cy = rooms[i].top  + rooms[i].height / 2;

        // Düşman yerleştir
        if (i % 3 == 0)      enemyManager.addEnemy(new Golem(cx, cy));
        else if (i % 3 == 1) enemyManager.addEnemy(new Goblin(cx, cy));
        else                  enemyManager.addEnemy(new Skeleton(cx, cy));

        // Her 3 odada bir normal sandık, her 5 odada bir kilitli sandık
        // Sandık düşmanın yanına değil, oda köşesine
        int chestX = rooms[i].left + 1;
        int chestY = rooms[i].top  + 1;
        if (map->getTile(chestX, chestY).getType() == TileType::FLOOR)
        {
            if (i % 5 == 0)
                map->addChest(new LockedChest(chestX, chestY));
            else if (i % 3 == 0)
                map->addChest(new NormalChest(chestX, chestY));
        }

        // Kilitli sandık için bazı odalara anahtar bırak
        if (i % 4 == 0)
            map->placeItem(cx - 1, cy, new Key());
    }

    return map;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler");
    window.setFramerateLimit(10);

    int currentFloor = 1;

    MapGenerator generator;
    EnemyManager enemyManager;
    Map* map = generateFloor(generator, enemyManager);

    // Oyuncuyu ilk FLOOR tile'a yerleştir
    int startX = 0, startY = 0;
    for (int y = 0; y < 50 && startX == 0; y++)
        for (int x = 0; x < 80 && startX == 0; x++)
            if (map->getTile(x, y).getType() == TileType::FLOOR)
            {
                startX = x;
                startY = y;
            }

    Player player(startX, startY);

    map->calculateFoV({player.getX(), player.getY()}, 10);

    sf::View camera;
    camera.setSize(1280.f, 800.f);

    // HUD için font
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/consola.ttf");

    // Kontrol tuşları metni — sabit, her zaman sağ üstte
    const std::vector<std::string> controls = {
        "KONTROLLER",
        "----------",
        "WASD  : Hareket",
        "E     : Sandik ac",
        "1-5   : Esya kullan",
        "SPC   : Envanter",
        "----------",
        "[ ] Normal sandik",
        "[M] Kilitli sandik",
        "[>] Merdiven"
    };

    // Ekran mesaj kuyruğu — son 5 mesaj altta görünür
    std::vector<std::string> messages;
    auto addMsg = [&](const std::string& msg) {
        messages.push_back(msg);
        if ((int)messages.size() > 5) messages.erase(messages.begin());
    };

    // Tuş tekrarını önlemek için basılı tuş takibi
    bool spaceWasPressed = false;
    bool fWasPressed     = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        bool playerMoved = player.handleInput(*map, enemyManager, addMsg);

        // --- MERDIVEN: oyuncu STAIRS üzerindeyse yeni kat üret ---
        if (player.isOnStairs(*map))
        {
            delete map;
            currentFloor++;
            addMsg("Kat " + std::to_string(currentFloor) + "'e gecis!");
            map = generateFloor(generator, enemyManager);

            // Oyuncuyu yeni katın ilk FLOOR tile'ına taşı
            for (int y = 0; y < 50; y++)
                for (int x = 0; x < 80; x++)
                    if (map->getTile(x, y).getType() == TileType::FLOOR)
                    {
                        // Entity protected x,y — Player public erişim sağlıyor
                        // Bunun için Player'a taşıma metodu ekledik
                        player.teleport(x, y);
                        goto doneSpawning;
                    }
            doneSpawning:;
        }

        // --- YERDE EŞYA: otomatik topla ---
        {
            Item* item = map->pickupItem(player.getX(), player.getY());
            if (item)
            {
                if (player.getInventory().addItem(item))
                    addMsg(item->getName() + " toplandi!");
                else
                {
                    addMsg("Envanter dolu! " + item->getName() + " birakildi.");
                    delete item;
                }
            }
        }

        // --- E: sandık aç ---
        bool eNow = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
        if (eNow && !fWasPressed)
        {
            Chest* chest = map->getChestAt(player.getX(), player.getY());
            if (chest) chest->open(player, addMsg);
            else       addMsg("Burada sandik yok.");
        }

        // --- SPACE: envanteri mesaj olarak göster ---
        bool spaceNow = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if (spaceNow && !spaceWasPressed)
        {
            const auto& items = player.getInventory().getItems();
            if (items.empty()) addMsg("Envanter bos.");
            else
            {
                addMsg("-- Envanter --");
                for (int i = 0; i < (int)items.size(); i++)
                    addMsg("[" + std::to_string(i) + "] " + items[i]->getName());
            }
        }
        spaceWasPressed = spaceNow;

        // --- 1-5: envanter slotunu kullan ---
        static const sf::Keyboard::Key numKeys[5] = {
            sf::Keyboard::Num1, sf::Keyboard::Num2, sf::Keyboard::Num3,
            sf::Keyboard::Num4, sf::Keyboard::Num5
        };
        bool fNow = false;
        for (int i = 0; i < 5; i++)
        {
            if (sf::Keyboard::isKeyPressed(numKeys[i]))
            {
                fNow = true;
                if (!fWasPressed)
                {
                    const auto& inv = player.getInventory().getItems();
                    if (i < (int)inv.size())
                    {
                        addMsg(inv[i]->getName() + " kullanildi!");
                        player.getInventory().useItem(i, player);
                    }
                    else addMsg("Slot " + std::to_string(i+1) + " bos.");
                }
                break;
            }
        }
        fWasPressed = fNow || eNow;

        // --- Ctrl+S: kaydet ---
        map->calculateFoV({player.getX(), player.getY()}, 10);

        // Düşmanlar sadece oyuncu tur harcadığında hareket eder / saldırır
        if (playerMoved)
        {
            int enemyDmg = enemyManager.updateAll(player.getX(), player.getY(), map);
            if (enemyDmg > 0)
            {
                int actual = std::max(1, enemyDmg - player.getDefense());
                player.setHp(player.getHp() - actual);
                addMsg("Dusmanlar sana " + std::to_string(actual) + " hasar verdi!");
            }
            enemyManager.removeDeadEnemies();
        }

        // Game over kontrolü
        if (!player.isAlive())
        {
            addMsg("=== OLDUUN! Yeniden basliyor... ===");
            // Ekranı bir frame daha göster, sonra sıfırla
            window.clear(sf::Color::Black);
            sf::Text goTxt;
            goTxt.setFont(font);
            goTxt.setString("GAME OVER\nHerhangi bir tusa bas...");
            goTxt.setCharacterSize(30);
            goTxt.setFillColor(sf::Color::Red);
            goTxt.setPosition(200.f, 260.f);
            window.draw(goTxt);
            window.display();

            // Herhangi bir tuşa basılana kadar bekle
            bool waiting = true;
            while (waiting)
            {
                sf::Event ev;
                while (window.pollEvent(ev))
                {
                    if (ev.type == sf::Event::Closed) { window.close(); waiting = false; }
                    if (ev.type == sf::Event::KeyPressed) waiting = false;
                }
            }

            // Oyunu sıfırla (floor 1'den başla)
            currentFloor = 1;
            delete map;
            map = generateFloor(generator, enemyManager);
            messages.clear();
            addMsg("Yeni oyun basladi!");

            // Oyuncuyu ilk FLOOR tile'a yeniden yerleştir
            player = Player(0, 0);
            for (int y = 0; y < 50; y++)
                for (int x = 0; x < 80; x++)
                    if (map->getTile(x, y).getType() == TileType::FLOOR)
                    { player.teleport(x, y); goto resetDone; }
            resetDone:;
        }

        camera.setCenter(player.getX() * 32.f + 16.f, player.getY() * 32.f + 16.f);
        window.setView(camera);

        window.clear(sf::Color::Black);
        map->draw(window);
        enemyManager.drawAll(window, map);
        player.draw(window);

        // --- HUD: UI view (sabit, kameradan bağımsız) ---
        sf::View uiView(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
        window.setView(uiView);

        // --- Kontrol tuşları (sağ üst, küçük) ---
        sf::RectangleShape hudBg(sf::Vector2f(160.f, (float)controls.size() * 14.f + 8.f));
        hudBg.setFillColor(sf::Color(0, 0, 0, 160));
        hudBg.setPosition(634.f, 4.f);
        window.draw(hudBg);

        for (int i = 0; i < (int)controls.size(); i++)
        {
            sf::Text txt;
            txt.setFont(font);
            txt.setString(controls[i]);
            txt.setCharacterSize(10);
            txt.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color(190, 190, 190));
            txt.setPosition(638.f, 7.f + i * 14.f);
            window.draw(txt);
        }

        // --- Sağ alt: HP ve DEF barları + envanter slotları ---
        {
            const float panelX = 530.f;
            const float panelY = 490.f;
            const float barW   = 160.f;
            const float barH   = 12.f;

            // Arka plan
            sf::RectangleShape panel(sf::Vector2f(266.f, 106.f));
            panel.setFillColor(sf::Color(0, 0, 0, 170));
            panel.setPosition(panelX - 4.f, panelY - 4.f);
            window.draw(panel);

            // HP barı
            int hp    = player.getHp();
            int maxHp = player.getMaxHp();
            float hpRatio = (float)hp / maxHp;

            sf::RectangleShape hpBg(sf::Vector2f(barW, barH));
            hpBg.setFillColor(sf::Color(80, 0, 0));
            hpBg.setPosition(panelX + 40.f, panelY);
            window.draw(hpBg);

            sf::RectangleShape hpBar(sf::Vector2f(barW * hpRatio, barH));
            hpBar.setFillColor(sf::Color(210, 40, 40));
            hpBar.setPosition(panelX + 40.f, panelY);
            window.draw(hpBar);

            sf::Text hpTxt; hpTxt.setFont(font); hpTxt.setCharacterSize(10);
            hpTxt.setString("HP " + std::to_string(hp) + "/" + std::to_string(maxHp));
            hpTxt.setFillColor(sf::Color::White);
            hpTxt.setPosition(panelX, panelY);
            window.draw(hpTxt);

            // DEF barı (max 20 def sayılır)
            int def = player.getDefense();
            float defRatio = std::min(1.f, (float)def / 20.f);

            sf::RectangleShape defBg(sf::Vector2f(barW, barH));
            defBg.setFillColor(sf::Color(0, 0, 80));
            defBg.setPosition(panelX + 40.f, panelY + 18.f);
            window.draw(defBg);

            sf::RectangleShape defBar(sf::Vector2f(barW * defRatio, barH));
            defBar.setFillColor(sf::Color(60, 100, 220));
            defBar.setPosition(panelX + 40.f, panelY + 18.f);
            window.draw(defBar);

            sf::Text defTxt; defTxt.setFont(font); defTxt.setCharacterSize(10);
            defTxt.setString("DEF " + std::to_string(def));
            defTxt.setFillColor(sf::Color::White);
            defTxt.setPosition(panelX, panelY + 18.f);
            window.draw(defTxt);

            // ATK göstergesi
            sf::Text atkTxt; atkTxt.setFont(font); atkTxt.setCharacterSize(10);
            atkTxt.setString("ATK " + std::to_string(player.getAttack()));
            atkTxt.setFillColor(sf::Color(255, 200, 80));
            atkTxt.setPosition(panelX, panelY + 36.f);
            window.draw(atkTxt);

            // Envanter slotları (1-5)
            const auto& items = player.getInventory().getItems();
            for (int i = 0; i < 5; i++)
            {
                float slotX = panelX + i * 52.f;
                float slotY = panelY + 54.f;

                sf::RectangleShape slot(sf::Vector2f(48.f, 36.f));
                slot.setFillColor(sf::Color(30, 30, 30));
                slot.setOutlineThickness(1.f);
                slot.setOutlineColor(sf::Color(120, 120, 120));
                slot.setPosition(slotX, slotY);
                window.draw(slot);

                // Slot numarası
                sf::Text numTxt; numTxt.setFont(font); numTxt.setCharacterSize(9);
                numTxt.setString(std::to_string(i + 1));
                numTxt.setFillColor(sf::Color(150, 150, 150));
                numTxt.setPosition(slotX + 2.f, slotY + 2.f);
                window.draw(numTxt);

                // Eşya adı (varsa)
                if (i < (int)items.size())
                {
                    std::string name = items[i]->getName();
                    if (name.size() > 6) name = name.substr(0, 6);
                    sf::Text itemTxt; itemTxt.setFont(font); itemTxt.setCharacterSize(9);
                    itemTxt.setString(name);
                    itemTxt.setFillColor(sf::Color(220, 220, 100));
                    itemTxt.setPosition(slotX + 2.f, slotY + 18.f);
                    window.draw(itemTxt);
                }
            }
        }

        // --- Mesaj kuyruğu (alt, son 5 mesaj) ---
        if (!messages.empty())
        {
            float msgH = (float)messages.size() * 14.f + 6.f;
            sf::RectangleShape msgBg(sf::Vector2f(400.f, msgH));
            msgBg.setFillColor(sf::Color(0, 0, 0, 150));
            msgBg.setPosition(4.f, 600.f - msgH - 4.f);
            window.draw(msgBg);

            for (int i = 0; i < (int)messages.size(); i++)
            {
                sf::Text txt;
                txt.setFont(font);
                txt.setString(messages[i]);
                txt.setCharacterSize(10);
                txt.setFillColor(sf::Color(220, 220, 180));
                txt.setPosition(8.f, 600.f - msgH - 1.f + i * 14.f);
                window.draw(txt);
            }
        }

        window.display();
    }

    delete map;
    return 0;
}
