#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <vector>

// Kısa ses efektleri (SFX) için singleton.
// SoundBuffer'lar cache'lenir, sf::Sound havuzu içinden bo�� olan kullanılır.
// Dosya yoksa sessizce geçer (oyun çökmez).
class SoundManager
{
public:
    static SoundManager& instance();

    // İlk çalmadan önce buffer'ı diskten yükle (opsiyonel; play() de yüklemeyi dener).
    // false dönerse dosya yok / okunamadı.
    bool preload(const std::string& path);

    // Sesi tek sefer çalar. Aynı ses üst üste çalabilir.
    void play(const std::string& path, float volume = 80.f);

    void setMasterVolume(float v); // 0..100

private:
    SoundManager() = default;
    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    sf::SoundBuffer* getBuffer(const std::string& path);
    sf::Sound& acquireSound();  // boş slot bul veya yenisini oluştur

    std::unordered_map<std::string, sf::SoundBuffer> buffers_;
    std::vector<sf::Sound> pool_;
    float masterVolume_ = 80.f;
    static constexpr std::size_t MAX_SOUNDS = 16;
};
