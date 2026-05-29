#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::instance()
{
    static SoundManager s;
    return s;
}

sf::SoundBuffer* SoundManager::getBuffer(const std::string& path)
{
    auto it = buffers_.find(path);
    if (it != buffers_.end()) return &it->second;

    sf::SoundBuffer buf;
    if (!buf.loadFromFile(path))
    {
        std::cerr << "[SoundManager] ses dosyasi bulunamadi: " << path << "\n";
        return nullptr;
    }
    auto [ins, ok] = buffers_.emplace(path, std::move(buf));
    return &ins->second;
}

bool SoundManager::preload(const std::string& path)
{
    return getBuffer(path) != nullptr;
}

sf::Sound& SoundManager::acquireSound()
{
    // İlk kullanımda havuzu sabit boyutta hazırla — vector reallocate
    // edince sf::Sound move'lanır ve OpenAL kaynakları bozulur.
    if (pool_.empty())
        pool_.resize(MAX_SOUNDS);

    // Önce boşta olan slotu ara
    for (auto& s : pool_)
        if (s.getStatus() != sf::Sound::Playing)
            return s;

    // Hepsi çalıyor — en eskiyi gasp et
    return pool_.front();
}

void SoundManager::play(const std::string& path, float volume)
{
    sf::SoundBuffer* buf = getBuffer(path);
    if (!buf) return;

    sf::Sound& s = acquireSound();
    s.setBuffer(*buf);
    s.setVolume(std::min(100.f, volume * (masterVolume_ / 100.f)));
    s.play();
}

void SoundManager::setMasterVolume(float v)
{
    masterVolume_ = v;
}
