#include "Map.h"
#include "NormalChest.h"
#include "LockedChest.h"

Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;

    grid.resize(height, std::vector<Tile>(width, Tile(TileType::WALL, false)));
}

Tile& Map::getTile(int x, int y)
{
    return grid[y][x];
}

void Map::setTile(int x, int y, TileType t)
{
    bool walkable = (t == TileType::FLOOR || t == TileType::STAIRS);
    grid[y][x] = Tile(t, walkable);
}

void Map::draw(sf::RenderWindow& window)
{
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            grid[y][x].draw(window, x, y);

    // FoV içindeki chest'leri çiz
    for (Chest* c : chests)
        if (grid[c->getY()][c->getX()].isVisible())
            c->draw(window);
}

void Map::resetVisibility()
{
    for (auto& row : grid)
        for (auto& tile : row)
            tile.setVisible(false);
}

// ── Recursive Shadowcasting ─────────────────────────────────────────────────
// Her oktant için ayrı çağrılır.
// (xx,xy,yx,yy) → lokal (dx,dy) koordinatlarını dünya koordinatlarına döndürür.
// start/end → taranacak eğim aralığı [0.0, 1.0].
static void castLight(std::vector<std::vector<Tile>>& grid, int w, int h,
                      int cx, int cy, int row, float start, float end,
                      int radius, int xx, int xy, int yx, int yy)
{
    if (start < end) return;

    int radiusSq = radius * radius;
    float newStart = 0.f;

    for (int j = row; j <= radius; j++)
    {
        bool blocked = false;

        for (int dx = -j, dy = -j; dx <= 0; dx++)
        {
            // Lokal → dünya koordinatı
            int X = cx + dx * xx + dy * xy;
            int Y = cy + dx * yx + dy * yy;

            // Bu hücrenin sol ve sağ eğim değerleri
            float lSlope = (dx - 0.5f) / (dy + 0.5f);
            float rSlope = (dx + 0.5f) / (dy - 0.5f);

            if (start < rSlope) continue; // Henüz ışık konisine girmedik
            if (end   > lSlope) break;    // Koniyi geçtik

            // Daire yarıçapı içindeyse aydınlat
            if (dx * dx + dy * dy < radiusSq &&
                X >= 0 && X < w && Y >= 0 && Y < h)
            {
                grid[Y][X].setVisible(true);
                grid[Y][X].setExplored(true);
            }

            bool opaque = (X < 0 || X >= w || Y < 0 || Y >= h ||
                           grid[Y][X].getType() == TileType::WALL);

            if (blocked)
            {
                // Önceki kare de duvardy; gölge aralığını daralt
                if (opaque)
                    newStart = rSlope;
                else
                {
                    blocked   = false;
                    start     = newStart;
                }
            }
            else if (opaque && j < radius)
            {
                // Duvarla karşılaştık → alt oktantı başlat, bu oktantı daralt
                blocked = true;
                castLight(grid, w, h, cx, cy, j + 1, start, lSlope,
                          radius, xx, xy, yx, yy);
                newStart = rSlope;
            }
        }

        // Satırın tamamı gölgedeyse daha uzağa bakmanın anlamı yok
        if (blocked) break;
    }
}

void Map::calculateFoV(sf::Vector2i pos, int radius)
{
    resetVisibility();

    // Oyuncunun bulunduğu kare her zaman görünür
    if (pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height)
    {
        grid[pos.y][pos.x].setVisible(true);
        grid[pos.y][pos.x].setExplored(true);
    }

    // 8 oktant için dönüşüm çarpanları
    static const int mult[4][8] = {
        { 1,  0,  0, -1, -1,  0,  0,  1 },
        { 0,  1, -1,  0,  0, -1,  1,  0 },
        { 0,  1,  1,  0,  0, -1, -1,  0 },
        { 1,  0,  0,  1, -1,  0,  0, -1 }
    };

    for (int oct = 0; oct < 8; oct++)
        castLight(grid, width, height, pos.x, pos.y, 1, 1.0f, 0.0f,
                  radius, mult[0][oct], mult[1][oct], mult[2][oct], mult[3][oct]);
}

void Map::addChest(Chest* chest)
{
    chests.push_back(chest);
}

Chest* Map::getChestAt(int x, int y)
{
    for (Chest* c : chests)
        if (c->getX() == x && c->getY() == y) return c;
    return nullptr;
}

void Map::placeItem(int x, int y, Item* item)
{
    itemsOnGround[{x, y}] = item;
}

Item* Map::pickupItem(int x, int y)
{
    auto it = itemsOnGround.find({x, y});
    if (it == itemsOnGround.end()) return nullptr;
    Item* item = it->second;
    itemsOnGround.erase(it);
    return item;
}

Map::~Map()
{
    for (auto& pair : itemsOnGround) delete pair.second;
    for (Chest* c : chests)         delete c;
}
