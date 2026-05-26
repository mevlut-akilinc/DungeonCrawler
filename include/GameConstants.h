#pragma once

// Oyunun tüm sabit sayıları — bir yerde değiştirilebilsin diye
namespace GameConstants
{
    // Harita
    constexpr int   MAP_WIDTH   = 80;
    constexpr int   MAP_HEIGHT  = 50;
    constexpr float TILE_SIZE   = 32.f;

    // Görüş (Field of View)
    constexpr int   FOV_RADIUS  = 10;

    // Pencere
    constexpr int   WINDOW_W    = 800;
    constexpr int   WINDOW_H    = 600;
    constexpr int   FRAMERATE   = 10;

    // Kamera (oyun dünyasını gösteren view)
    constexpr float CAMERA_W    = 1280.f;
    constexpr float CAMERA_H    = 800.f;

    // Mesaj kuyruğu maksimum boyutu
    constexpr int   MAX_MESSAGES = 5;

    // Envanter slot sayısı (1-5 tuşları)
    constexpr int   HOTBAR_SLOTS = 5;
}
