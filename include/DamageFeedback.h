#pragma once
#include <SFML/Graphics.hpp>

// Oyuncu hasar aldığında tetiklenen görsel geri bildirim:
//  - Ekran sarsıntısı (kamera offset)
//  - Kırmızı kenar vignette (4 kenar overlay)
// Her render frame'inde apply/draw çağrılır; süreler 0'a inince devre dışı kalır.
class DamageFeedback
{
private:
    int shakeFrames    = 0; // kalan sarsıntı frame'i
    int vignetteFrames = 0; // kalan vignette frame'i

public:
    // Hasar alındığında çağır — sarsıntı + vignette zamanlayıcılarını doldurur
    void trigger();

    // Kamera merkezi için (shakeX, shakeY) offset hesaplar ve sayaç düşer.
    // Sarsıntı yoksa (0, 0) döner.
    sf::Vector2f computeShakeOffset();

    // Vignette aktifse 4 kenar kırmızı overlay çizer, sayaç düşer.
    // window'un view'ini geçici olarak default view'a alır, sonra geri yükler.
    void drawVignette(sf::RenderWindow& window, int windowW, int windowH,
                      const sf::View& restoreView);
};
