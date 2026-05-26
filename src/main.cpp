#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>
#include <string>
#include <functional>

#include "GameConstants.h"
#include "Map.h"
#include "MapGenerator.h"
#include "Player.h"
#include "EnemyManager.h"
#include "FloorFactory.h"
#include "InputHandler.h"
#include "SaveManager.h"
#include "HUD.h"
#include "Menu.h"

using namespace GameConstants;

// ── Yardımcı fonksiyonlar ──────────────────────────────────────────────

// Oyuncunun durduğu kareye bırakılmış eşya varsa otomatik topla.
// skipPos eşittir oyuncu pozisyonu ise atlanır (yeni bırakılan eşya anında geri alınmasın diye).
static void autoPickup(Player &player, Map &map,
                       std::function<void(const std::string &)> addMsg,
                       sf::Vector2i skipPos)
{
    if (player.getX() == skipPos.x && player.getY() == skipPos.y)
        return;

    Item *item = map.pickupItem(player.getX(), player.getY());
    if (!item)
        return;

    if (player.getInventory().addItem(item))
        addMsg(item->getName() + " toplandi!");
    else
    {
        addMsg("Envanter dolu! " + item->getName() + " birakildi.");
        delete item;
    }
}

// Oyuncu STAIRS üzerindeyse yeni kat üretir ve yerleştirir
static void tryAdvanceFloor(Player &player, Map *&map, FloorFactory &factory,
                            int &currentFloor,
                            std::function<void(const std::string &)> addMsg)
{
    if (!player.isOnStairs(*map))
        return;

    delete map;
    currentFloor++;
    addMsg("Kat " + std::to_string(currentFloor) + "'e gecis!");
    map = factory.generateFloor(currentFloor);
    FloorFactory::spawnPlayer(player, *map);
}

// Oyun durumunu sıfırla (kat 1, yeni harita, oyuncu yeniden spawn)
static void resetGame(Player &player, Map *&map, FloorFactory &factory,
                      int &currentFloor, std::vector<std::string> &messages,
                      std::function<void(const std::string &)> addMsg)
{
    currentFloor = 1;
    delete map;
    map = factory.generateFloor(currentFloor);
    messages.clear();
    addMsg("Yeni oyun basladi!");

    player.reset();
    FloorFactory::spawnPlayer(player, *map);
}

// Ctrl+S / Ctrl+L / Ctrl+Q olaylarını işler
static void handleSaveLoadEvent(const sf::Event &event, sf::RenderWindow &window,
                                Player &player,
                                Map *&map, FloorFactory &factory,
                                MapGenerator &generator, EnemyManager &em,
                                int &currentFloor,
                                std::function<void(const std::string &)> addMsg)
{
    if (event.type != sf::Event::KeyPressed)
        return;

    bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
    if (!ctrl)
        return;

    if (event.key.code == sf::Keyboard::S)
    {
        bool ok = SaveManager::save("savegame.txt", player,
                                    generator.getLastSeed(), currentFloor, em);
        addMsg(ok ? "Oyun kaydedildi. (Kat: " + std::to_string(currentFloor) + ")"
                  : "Kayit hatasi!");
    }
    else if (event.key.code == sf::Keyboard::L)
    {
        unsigned int seed = 0;
        int savedFloor = 1;
        if (SaveManager::load("savegame.txt", player, seed, savedFloor, em))
        {
            currentFloor = savedFloor;
            delete map;
            srand(seed);
            map = factory.buildLayout();
            map->calculateFoV({player.getX(), player.getY()}, FOV_RADIUS);
            addMsg("Kayit yuklendi. (Kat: " + std::to_string(currentFloor) + ")");
        }
        else
            addMsg("Kayit dosyasi bulunamadi!");
    }
    else if (event.key.code == sf::Keyboard::Q)
    {
        window.close();
    }
}

// ── main ───────────────────────────────────────────────────────────────

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // Pencere
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Dungeon Crawler",
                            sf::Style::Default, settings);
    window.setFramerateLimit(FRAMERATE);

    // Oyun durumu
    int currentFloor = 1;
    MapGenerator generator;
    EnemyManager enemyManager;
    FloorFactory factory(generator, enemyManager);

    Map *map = factory.generateFloor(currentFloor);
    Player player(0, 0);
    FloorFactory::spawnPlayer(player, *map);
    map->calculateFoV({player.getX(), player.getY()}, FOV_RADIUS);

    // Kamera
    sf::View camera;
    camera.setSize(CAMERA_W, CAMERA_H);

    // Font + HUD + Menu
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/consola.ttf");
    HUD hud(font);
    Menu menu(font);

    // Açılış menüsü — kullanıcı kapatırsa çık
    if (!menu.showStart(window))
        return 0;

    // Mesaj kuyruğu
    std::vector<std::string> messages;
    auto addMsg = [&](const std::string &msg)
    {
        messages.push_back(msg);
        if ((int)messages.size() > MAX_MESSAGES)
            messages.erase(messages.begin());
    };

    // Input
    InputHandler input;

    // Yeni bırakılan item'in anında geri alınmasını engelleyen pozisyon (-1: yok)
    sf::Vector2i skipPickupAt(-1, -1);
    sf::Vector2i lastPos(player.getX(), player.getY());

    // ── Oyun döngüsü ──
    while (window.isOpen())
    {
        // 1) Event polling — pencere kapatma + Ctrl+S/L
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            handleSaveLoadEvent(event, window, player, map, factory,
                                generator, enemyManager, currentFloor, addMsg);
        }

        // 2) Hareket (tur tetikleyici)
        bool playerMoved = player.handleInput(*map, enemyManager, addMsg);

        // 3) Kat geçişi + otomatik item topla + aksiyon tuşları
        tryAdvanceFloor(player, map, factory, currentFloor, addMsg);

        // Oyuncu hareket ettiyse skip-pickup pozisyonunu temizle
        sf::Vector2i pos(player.getX(), player.getY());
        if (pos != lastPos)
        {
            skipPickupAt = sf::Vector2i(-1, -1);
            lastPos = pos;
        }

        autoPickup(player, *map, addMsg, skipPickupAt);

        bool dropped = input.processHeldKeys(player, *map, addMsg);
        if (dropped)
            skipPickupAt = pos; // bu kareyi bir sonraki harekete kadar yok say

        // 4) FoV güncelle
        map->calculateFoV({player.getX(), player.getY()}, FOV_RADIUS);

        // 5) Düşman turu (sadece oyuncu hareket ettiyse)
        bool tookDamageThisFrame = false;
        if (playerMoved)
        {
            enemyManager.updateAll(player.getX(), player.getY(), map);
            int netDmg = enemyManager.attackPlayer(player, addMsg);
            if (netDmg > 0)
                tookDamageThisFrame = true;
            enemyManager.removeDeadEnemies();
        }

        // 6) Game over kontrolü
        if (!player.isAlive())
        {
            if (!menu.showGameOver(window, currentFloor))
                break; // pencere kapandı
            resetGame(player, map, factory, currentFloor, messages, addMsg);
            // Reset sonrası state'i tazele
            skipPickupAt = sf::Vector2i(-1, -1);
            lastPos = sf::Vector2i(player.getX(), player.getY());
            continue;
        }

        // 7) Render
        camera.setCenter(player.getX() * TILE_SIZE + TILE_SIZE / 2.f,
                         player.getY() * TILE_SIZE + TILE_SIZE / 2.f);
        window.setView(camera);

        window.clear(sf::Color::Black);
        map->draw(window);
        enemyManager.drawAll(window, map);
        player.draw(window);

        // Hasar flash
        if (tookDamageThisFrame)
        {
            sf::RectangleShape flash(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            flash.setFillColor(sf::Color(255, 0, 0, 130));
            flash.setPosition(player.getX() * TILE_SIZE, player.getY() * TILE_SIZE);
            window.draw(flash);
        }

        hud.draw(window, player, messages);
        window.display();
    }

    delete map;
    return 0;
}
