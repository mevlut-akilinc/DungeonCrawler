#pragma once
#include <SFML/Audio.hpp>
#include <string>

class MusicManager
{
public:
    static MusicManager& instance();

    // Aynı dosya zaten çalıyorsa hiçbir şey yapma. Dosya yoksa sessizce geç.
    void play(const std::string& path, bool loop = true);
    void stop();
    void setVolume(float v);  // 0..100

private:
    MusicManager() = default;
    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;

    sf::Music music_;
    std::string currentPath_;
    float volume_ = 40.f;
};
