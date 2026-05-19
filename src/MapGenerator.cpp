#include "MapGenerator.h"
#include <cstdlib>
#include <ctime>

void MapGenerator::split(BSPNode* node)
{
    int w = node->area.width;
    int h = node->area.height;

    // İkiye bölünemeyecek kadar küçükse dur
    if (w < MIN_SIZE * 2 && h < MIN_SIZE * 2)
        return;

    // Yatay mı dikey mi keseceğiz?
    bool splitHorizontal;
    if (w < MIN_SIZE * 2)
        splitHorizontal = true;
    else if (h < MIN_SIZE * 2)
        splitHorizontal = false;
    else
        splitHorizontal = (rand() % 2 == 0);

    node->left  = new BSPNode();
    node->right = new BSPNode();

    if (splitHorizontal)
    {
        // Yukarı / aşağı böl
        int splitY = node->area.top + MIN_SIZE + rand() % (h - MIN_SIZE * 2 + 1);
        node->left->area  = sf::IntRect(node->area.left, node->area.top, w, splitY - node->area.top);
        node->right->area = sf::IntRect(node->area.left, splitY, w, node->area.top + h - splitY);
    }
    else
    {
        // Sol / sağ böl
        int splitX = node->area.left + MIN_SIZE + rand() % (w - MIN_SIZE * 2 + 1);
        node->left->area  = sf::IntRect(node->area.left, node->area.top, splitX - node->area.left, h);
        node->right->area = sf::IntRect(splitX, node->area.top, node->area.left + w - splitX, h);
    }

    split(node->left);
    split(node->right);
}

void MapGenerator::createRooms(BSPNode* node, Map& map)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        // Yaprak node — oda oluştur
        int roomW = MIN_SIZE - 1 + rand() % (node->area.width  - MIN_SIZE + 1);
        int roomH = MIN_SIZE - 1 + rand() % (node->area.height - MIN_SIZE + 1);
        int roomX = node->area.left + rand() % (node->area.width  - roomW);
        int roomY = node->area.top  + rand() % (node->area.height - roomH);

        node->room = sf::IntRect(roomX, roomY, roomW, roomH);

        for (int y = roomY; y < roomY + roomH; y++)
            for (int x = roomX; x < roomX + roomW; x++)
                map.setTile(x, y, TileType::FLOOR);

        return;
    }

    if (node->left)  createRooms(node->left,  map);
    if (node->right) createRooms(node->right, map);
}

sf::Vector2i MapGenerator::getRoomCenter(BSPNode* node)
{
    // Yaprak node'a in, odanın merkezini döndür
    if (node->left == nullptr && node->right == nullptr)
    {
        return sf::Vector2i(
            node->room.left + node->room.width  / 2,
            node->room.top  + node->room.height / 2
        );
    }
    // Yaprak değilse sol çocuğa git
    if (node->left)  return getRoomCenter(node->left);
    return getRoomCenter(node->right);
}

void MapGenerator::connectRooms(BSPNode* node, Map& map)
{
    if (node->left == nullptr || node->right == nullptr)
        return;

    sf::Vector2i a = getRoomCenter(node->left);
    sf::Vector2i b = getRoomCenter(node->right);

    // Önce yatay, sonra dikey L şekli
    int stepX = (a.x < b.x) ? 1 : -1;
    for (int x = a.x; x != b.x; x += stepX)
        map.setTile(x, a.y, TileType::FLOOR);

    int stepY = (a.y < b.y) ? 1 : -1;
    for (int y = a.y; y != b.y; y += stepY)
        map.setTile(b.x, y, TileType::FLOOR);

    connectRooms(node->left,  map);
    connectRooms(node->right, map);
}

Map* MapGenerator::generate(int width, int height)
{
    srand(time(nullptr));

    Map* map = new Map(width, height);

    BSPNode* root = new BSPNode();
    root->area = sf::IntRect(0, 0, width, height);

    split(root);
    createRooms(root, *map);   // * ekledik
    connectRooms(root, *map);  // * ekledik

    return map;
}
