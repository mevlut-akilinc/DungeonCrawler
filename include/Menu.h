#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

// Oyun dışı tam ekran menüler: Açılış (Hoşgeldin) ve Game Over.
// İkisi de aynı görsel konsepti paylaşır — tek bir Menu sınıfında toplandı.
class Menu
{
public:
    explicit Menu(sf::Font& font);

    // Açılış ekranı — ENTER'a basana kadar bekler
    // Dönüş: false → pencere kapatıldı (oyunu başlatma)
    bool showStart(sf::RenderWindow& window);

    // Game over ekranı — ENTER'a basana kadar bekler
    // Dönüş: false → pencere kapatıldı (yeniden başlatma)
    bool showGameOver(sf::RenderWindow& window, int floorReached);

private:
    sf::Font& font_;

    // Ortak çizim: başlık, gövde satırları, alttaki buton
    // Tek bir frame çizer — çağıran tarafın display() ve event loop'u var
    void drawFrame(sf::RenderWindow& window,
                   const std::string& title,
                   sf::Color titleColor,
                   const std::vector<std::string>& body,
                   const std::string& button);

    // Ortak event loop: ENTER → true, Close → false
    bool waitForEnter(sf::RenderWindow& window,
                      const std::string& title,
                      sf::Color titleColor,
                      const std::vector<std::string>& body,
                      const std::string& button);
};
