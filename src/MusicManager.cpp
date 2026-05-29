#include "MusicManager.h"
#include <iostream>

MusicManager& MusicManager::instance()
{
    static MusicManager inst;
    return inst;
}

void MusicManager::play(const std::string& path, bool loop)
{
    if (path == currentPath_ && music_.getStatus() == sf::Music::Playing)
        return;

    music_.stop();

    if (!music_.openFromFile(path))
    {
        std::cerr << "[MusicManager] muzik dosyasi bulunamadi: " << path << "\n";
        currentPath_.clear();
        return;
    }

    music_.setLoop(loop);
    music_.setVolume(volume_);
    music_.play();
    currentPath_ = path;
}

void MusicManager::stop()
{
    music_.stop();
    currentPath_.clear();
}

void MusicManager::setVolume(float v)
{
    volume_ = v;
    music_.setVolume(volume_);
}
