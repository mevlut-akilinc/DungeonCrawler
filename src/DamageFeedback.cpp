#include "DamageFeedback.h"
#include <cstdlib>
#include <algorithm>

void DamageFeedback::trigger()
{
    shakeFrames    = 4;
    vignetteFrames = 4;
}

sf::Vector2f DamageFeedback::computeShakeOffset()
{
    if (shakeFrames <= 0) return sf::Vector2f(0.f, 0.f);

    // 4 frame'lik sönen sarsıntı: 40, 30, 20, 10 world px
    float mag = shakeFrames * 10.f;
    float ox  = (((rand() % 200) - 100) / 100.f) * mag;
    float oy  = (((rand() % 200) - 100) / 100.f) * mag;
    --shakeFrames;
    return sf::Vector2f(ox, oy);
}

void DamageFeedback::drawVignette(sf::RenderWindow& window, int windowW, int windowH,
                                  const sf::View& restoreView)
{
    if (vignetteFrames <= 0) return;

    window.setView(window.getDefaultView()); // HUD koordinatlarına geç

    sf::Uint8 alpha = static_cast<sf::Uint8>(std::min(220, vignetteFrames * 45));
    sf::Color red(220, 25, 25, alpha);
    float thick = 50.f;

    sf::RectangleShape band;
    band.setFillColor(red);

    // üst
    band.setSize(sf::Vector2f((float)windowW, thick));
    band.setPosition(0.f, 0.f);
    window.draw(band);
    // alt
    band.setSize(sf::Vector2f((float)windowW, thick));
    band.setPosition(0.f, (float)windowH - thick);
    window.draw(band);
    // sol
    band.setSize(sf::Vector2f(thick, (float)windowH));
    band.setPosition(0.f, 0.f);
    window.draw(band);
    // sağ
    band.setSize(sf::Vector2f(thick, (float)windowH));
    band.setPosition((float)windowW - thick, 0.f);
    window.draw(band);

    window.setView(restoreView);
    --vignetteFrames;
}
