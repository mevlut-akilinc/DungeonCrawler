#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include "Player.h"
#include "Map.h"

// Basılı tuş tabanlı oyun aksiyonlarını yönetir:
//   E       → sandık aç
//   1-5     → envanter slotu kullan
//   C+1-5   → envanter slotunu yere bırak
//   SPACE   → envanteri mesaj kuyruğunda göster
//
// Edge-detect (tek basışta tek tetik) state'lerini içeride tutar.
class InputHandler
{
public:
    using MsgCallback = std::function<void(const std::string&)>;

    InputHandler() = default;

    // Her frame çağrılır — basılı tuşlara göre aksiyonları tetikler
    // Döndürür: bu frame içinde bir item bırakıldıysa true
    bool processHeldKeys(Player& player, Map& map, MsgCallback addMsg);

private:
    bool spaceWasPressed_ = false;
    bool actionKeyWasPressed_ = false;
};
