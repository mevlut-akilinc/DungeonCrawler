#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.h"

class HUD
{
public:
    explicit HUD(sf::Font& font);

    // Her frame çağrılır — tüm HUD öğelerini çizer
    void draw(sf::RenderWindow& window,
              const Player& player,
              const std::vector<std::string>& messages);

private:
    sf::Font& font_;
    std::vector<std::string> controls_;

    void drawControls  (sf::RenderWindow& window);
    void drawStatsPanel(sf::RenderWindow& window, const Player& player);
    void drawMessages  (sf::RenderWindow& window, const std::vector<std::string>& messages);
};
