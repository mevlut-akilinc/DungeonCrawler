// Game.h — tanımlı fakat kullanılmıyor; main.cpp doğrudan game loop çalıştırıyor.
// Refactor maliyetli olduğundan şimdilik pasif bırakıldı.
/*
#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"

enum class GameState
{
    MENU,
    PLAYING,
    GAME_OVER
};

class Game
{
private:
    sf::RenderWindow window;
    Map *map;
    Player *player;
    GameState state;

public:
    Game();
    void run();
    void update();
    void render();
};
*/
