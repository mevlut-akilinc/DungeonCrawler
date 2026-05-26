#include "Menu.h"
#include "GameConstants.h"

using namespace GameConstants;

Menu::Menu(sf::Font& font) : font_(font) {}

// ── Ortak iskelet: arka plan + çerçeve + başlık + gövde + buton ─────────
void Menu::drawFrame(sf::RenderWindow& window,
                     const std::string& title,
                     sf::Color titleColor,
                     const std::vector<std::string>& body,
                     const std::string& button)
{
    // UI view (sabit ekran koordinatları)
    sf::View view(sf::FloatRect(0.f, 0.f, (float)WINDOW_W, (float)WINDOW_H));
    window.setView(view);

    // Koyu arka plan
    window.clear(sf::Color(15, 12, 20));

    // Orta panel
    const float panelW = 520.f;
    const float panelH = 380.f;
    const float panelX = (WINDOW_W - panelW) / 2.f;
    const float panelY = (WINDOW_H - panelH) / 2.f;

    sf::RectangleShape panel(sf::Vector2f(panelW, panelH));
    panel.setFillColor(sf::Color(25, 20, 35));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(120, 100, 60));
    panel.setPosition(panelX, panelY);
    window.draw(panel);

    // Başlık
    sf::Text titleTxt;
    titleTxt.setFont(font_);
    titleTxt.setString(title);
    titleTxt.setCharacterSize(34);
    titleTxt.setFillColor(titleColor);
    titleTxt.setStyle(sf::Text::Bold);
    sf::FloatRect tb = titleTxt.getLocalBounds();
    titleTxt.setPosition(panelX + (panelW - tb.width) / 2.f - tb.left,
                         panelY + 35.f);
    window.draw(titleTxt);

    // Başlık altı ayraç çizgi
    sf::RectangleShape sep(sf::Vector2f(panelW - 80.f, 2.f));
    sep.setFillColor(sf::Color(120, 100, 60));
    sep.setPosition(panelX + 40.f, panelY + 90.f);
    window.draw(sep);

    // Gövde — satır satır
    float bodyY = panelY + 115.f;
    for (const auto& line : body)
    {
        sf::Text txt;
        txt.setFont(font_);
        txt.setString(line);
        txt.setCharacterSize(14);
        txt.setFillColor(sf::Color(200, 200, 180));
        sf::FloatRect b = txt.getLocalBounds();
        txt.setPosition(panelX + (panelW - b.width) / 2.f - b.left, bodyY);
        window.draw(txt);
        bodyY += 22.f;
    }

    // Alt buton (sarı çerçeve içinde)
    const float btnW = 280.f;
    const float btnH = 38.f;
    const float btnX = panelX + (panelW - btnW) / 2.f;
    const float btnY = panelY + panelH - 60.f;

    sf::RectangleShape btn(sf::Vector2f(btnW, btnH));
    btn.setFillColor(sf::Color(45, 35, 15));
    btn.setOutlineThickness(2.f);
    btn.setOutlineColor(sf::Color(255, 210, 0));
    btn.setPosition(btnX, btnY);
    window.draw(btn);

    sf::Text btnTxt;
    btnTxt.setFont(font_);
    btnTxt.setString(button);
    btnTxt.setCharacterSize(15);
    btnTxt.setStyle(sf::Text::Bold);
    btnTxt.setFillColor(sf::Color(255, 220, 80));
    sf::FloatRect bb = btnTxt.getLocalBounds();
    btnTxt.setPosition(btnX + (btnW - bb.width) / 2.f - bb.left,
                       btnY + (btnH - bb.height) / 2.f - bb.top);
    window.draw(btnTxt);
}

bool Menu::waitForEnter(sf::RenderWindow& window,
                        const std::string& title, sf::Color titleColor,
                        const std::vector<std::string>& body,
                        const std::string& button)
{
    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) { window.close(); return false; }
            if (ev.type == sf::Event::KeyPressed &&
                (ev.key.code == sf::Keyboard::Enter ||
                 ev.key.code == sf::Keyboard::Space))
                return true;
        }

        drawFrame(window, title, titleColor, body, button);
        window.display();
    }
    return false;
}

bool Menu::showStart(sf::RenderWindow& window)
{
    return waitForEnter(window,
        "DUNGEON CRAWLER",
        sf::Color(255, 210, 0),
        {
            "Karanlik dungeonlari kesfet, dusmanlari yen,",
            "sandiklari ac ve daha derinlere in.",
            "",
            "WASD ile hareket et.",
            "Dusmanlarin uzerine yuruyerek saldir.",
            "E ile sandik ac, 1-5 ile esya kullan.",
            "C+1-5 ile elindeki esyayi yere birak.",
            "",
            "Hayatta kal ve katlari yukseltebildigin",
            "kadar yukselt!"
        },
        "[ ENTER : OYUNA BASLA ]"
    );
}

bool Menu::showGameOver(sf::RenderWindow& window, int floorReached)
{
    return waitForEnter(window,
        "GAME OVER",
        sf::Color(220, 60, 60),
        {
            "Maceran burada bitti...",
            "",
            "Ulasilan kat: " + std::to_string(floorReached),
            "",
            "Karanliklar seni yendi ama bir sonraki",
            "denemende daha derine inebilirsin.",
            "",
            "Pesini birakma."
        },
        "[ ENTER : YENIDEN BASLA ]"
    );
}
