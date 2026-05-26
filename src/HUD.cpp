#include "HUD.h"
#include <algorithm>

HUD::HUD(sf::Font& font) : font_(font)
{
    controls_ = {
        "KONTROLLER",
        "----------",
        "WASD   : Hareket",
        "E      : Sandik ac",
        "1-5    : Esya kullan",
        "C+1-5  : Esya birak",
        "SPC    : Envanter",
        "----------",
        "Ctrl+S : Kaydet",
        "Ctrl+L : Yukle",
        "Ctrl+Q : Cikis"
    };
}

void HUD::draw(sf::RenderWindow& window,
               const Player& player,
               const std::vector<std::string>& messages)
{
    // HUD sabit ekran koordinatlarında çizilir — kameradan bağımsız
    sf::View uiView(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    window.setView(uiView);

    drawControls(window);
    drawStatsPanel(window, player);
    drawMessages(window, messages);
}

// --- Sağ üst: kontrol tuşları paneli ---
void HUD::drawControls(sf::RenderWindow& window)
{
    const float panelW = 160.f;
    const float lineH  = 14.f;
    const float panelH = (float)controls_.size() * lineH + 8.f;

    sf::RectangleShape bg(sf::Vector2f(panelW, panelH));
    bg.setFillColor(sf::Color(0, 0, 0, 160));
    bg.setPosition(634.f, 4.f);
    window.draw(bg);

    for (int i = 0; i < (int)controls_.size(); i++)
    {
        sf::Text txt;
        txt.setFont(font_);
        txt.setString(controls_[i]);
        txt.setCharacterSize(10);
        txt.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color(190, 190, 190));
        txt.setPosition(638.f, 7.f + i * lineH);
        window.draw(txt);
    }
}

// --- Sağ alt: HP/DEF barları, ATK, silah, envanter slotları ---
void HUD::drawStatsPanel(sf::RenderWindow& window, const Player& player)
{
    const float panelX = 530.f;
    const float panelY = 468.f;
    const float barW   = 160.f;
    const float barH   = 12.f;

    // Panel arka planı
    sf::RectangleShape panel(sf::Vector2f(266.f, 128.f));
    panel.setFillColor(sf::Color(0, 0, 0, 170));
    panel.setPosition(panelX - 4.f, panelY - 4.f);
    window.draw(panel);

    // HP barı
    int hp       = player.getHp();
    int maxHp    = player.getMaxHp();
    float hpRatio = (float)hp / maxHp;

    sf::RectangleShape hpBg(sf::Vector2f(barW, barH));
    hpBg.setFillColor(sf::Color(80, 0, 0));
    hpBg.setPosition(panelX + 40.f, panelY);
    window.draw(hpBg);

    sf::RectangleShape hpBar(sf::Vector2f(barW * hpRatio, barH));
    hpBar.setFillColor(sf::Color(210, 40, 40));
    hpBar.setPosition(panelX + 40.f, panelY);
    window.draw(hpBar);

    sf::Text hpTxt;
    hpTxt.setFont(font_); hpTxt.setCharacterSize(10);
    hpTxt.setString("HP " + std::to_string(hp) + "/" + std::to_string(maxHp));
    hpTxt.setFillColor(sf::Color::White);
    hpTxt.setPosition(panelX, panelY);
    window.draw(hpTxt);

    // DEF barı (max 20 def baz alınır)
    int def = player.getDefense();
    float defRatio = std::min(1.f, (float)def / 20.f);

    sf::RectangleShape defBg(sf::Vector2f(barW, barH));
    defBg.setFillColor(sf::Color(0, 0, 80));
    defBg.setPosition(panelX + 40.f, panelY + 18.f);
    window.draw(defBg);

    sf::RectangleShape defBar(sf::Vector2f(barW * defRatio, barH));
    defBar.setFillColor(sf::Color(60, 100, 220));
    defBar.setPosition(panelX + 40.f, panelY + 18.f);
    window.draw(defBar);

    sf::Text defTxt;
    defTxt.setFont(font_); defTxt.setCharacterSize(10);
    defTxt.setString("DEF " + std::to_string(def));
    defTxt.setFillColor(sf::Color::White);
    defTxt.setPosition(panelX, panelY + 18.f);
    window.draw(defTxt);

    // ATK göstergesi
    sf::Text atkTxt;
    atkTxt.setFont(font_); atkTxt.setCharacterSize(10);
    atkTxt.setString("ATK " + std::to_string(player.getAttack()));
    atkTxt.setFillColor(sf::Color(255, 200, 80));
    atkTxt.setPosition(panelX, panelY + 36.f);
    window.draw(atkTxt);

    // Kuşanılmış silah
    sf::Text wpTxt;
    wpTxt.setFont(font_); wpTxt.setCharacterSize(10);
    std::string wpStr = "Silah: -";
    if (player.getEquippedWeapon())
        wpStr = "Silah: " + player.getEquippedWeapon()->getName();
    wpTxt.setString(wpStr);
    wpTxt.setFillColor(sf::Color(180, 255, 180));
    wpTxt.setPosition(panelX, panelY + 54.f);
    window.draw(wpTxt);

    // Envanter slotları 1–5
    const auto& items = player.getInventory().getItems();
    for (int i = 0; i < 5; i++)
    {
        float slotX = panelX + i * 52.f;
        float slotY = panelY + 72.f;

        bool isEquipped = (i < (int)items.size() &&
                           player.getEquippedWeapon() == items[i]);

        sf::RectangleShape slot(sf::Vector2f(48.f, 36.f));
        slot.setFillColor(isEquipped ? sf::Color(50, 45, 10) : sf::Color(30, 30, 30));
        slot.setOutlineThickness(isEquipped ? 2.f : 1.f);
        slot.setOutlineColor(isEquipped ? sf::Color(255, 210, 0) : sf::Color(120, 120, 120));
        slot.setPosition(slotX, slotY);
        window.draw(slot);

        sf::Text numTxt;
        numTxt.setFont(font_); numTxt.setCharacterSize(9);
        numTxt.setString(std::to_string(i + 1));
        numTxt.setFillColor(sf::Color(150, 150, 150));
        numTxt.setPosition(slotX + 2.f, slotY + 2.f);
        window.draw(numTxt);

        if (i < (int)items.size())
        {
            std::string name = items[i]->getName();
            if (name.size() > 6) name = name.substr(0, 6);

            sf::Text itemTxt;
            itemTxt.setFont(font_); itemTxt.setCharacterSize(9);
            itemTxt.setString(name);
            itemTxt.setFillColor(isEquipped ? sf::Color(255, 210, 0) : sf::Color(220, 220, 100));
            itemTxt.setPosition(slotX + 2.f, slotY + 18.f);
            window.draw(itemTxt);
        }
    }
}

// --- Sol alt: son 5 mesaj ---
void HUD::drawMessages(sf::RenderWindow& window,
                       const std::vector<std::string>& messages)
{
    if (messages.empty()) return;

    float msgH = (float)messages.size() * 14.f + 6.f;

    sf::RectangleShape msgBg(sf::Vector2f(400.f, msgH));
    msgBg.setFillColor(sf::Color(0, 0, 0, 150));
    msgBg.setPosition(4.f, 600.f - msgH - 4.f);
    window.draw(msgBg);

    for (int i = 0; i < (int)messages.size(); i++)
    {
        sf::Text txt;
        txt.setFont(font_);
        txt.setString(messages[i]);
        txt.setCharacterSize(10);
        txt.setFillColor(sf::Color(220, 220, 180));
        txt.setPosition(8.f, 600.f - msgH - 1.f + i * 14.f);
        window.draw(txt);
    }
}
