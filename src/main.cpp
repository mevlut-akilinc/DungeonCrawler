#include <SFML/Graphics.hpp>
#include "Map.h"
#include "MapGenerator.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Goblin.h"
#include "Skeleton.h"
#include "Golem.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dungeon Crawler");
    window.setFramerateLimit(10);

    MapGenerator generator;
    Map* map = generator.generate(80, 50);

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

    // Her odaya (ilk oda hariç) bir düşman yerleştir
    EnemyManager enemyManager;
    const auto& rooms = generator.getRooms();
    for (size_t i = 1; i < rooms.size(); i++)
    {
        int cx = rooms[i].left + rooms[i].width  / 2;
        int cy = rooms[i].top  + rooms[i].height / 2;

        // Oda sırasına göre dönüşümlü düşman türleri
        if (i % 3 == 0)      enemyManager.addEnemy(new Golem(cx, cy));
        else if (i % 3 == 1) enemyManager.addEnemy(new Goblin(cx, cy));
        else                  enemyManager.addEnemy(new Skeleton(cx, cy));
    }

    // Oyun başında ilk görüş alanını hesapla
    map->calculateFoV({startX, startY}, 10);

    sf::View camera;
    camera.setSize(1280.f, 800.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.handleInput(*map);

        // Görüş alanını güncelle
        map->calculateFoV({player.getX(), player.getY()}, 10);

        // Düşman AI güncelle + ölüleri temizle
        enemyManager.updateAll(player.getX(), player.getY(), map);
        enemyManager.removeDeadEnemies();

        // Kamera oyuncuyu takip et
        camera.setCenter(player.getX() * 32.f + 16.f, player.getY() * 32.f + 16.f);
        window.setView(camera);

        window.clear(sf::Color::Black);
        map->draw(window);
        enemyManager.drawAll(window, map); // FoV içindeki düşmanları çiz
        player.draw(window);
        window.display();
    }

    delete map;
    return 0;
}
