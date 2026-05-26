#include "TextureManager.h"
#include <iostream>

TextureManager& TextureManager::instance()
{
    static TextureManager inst;
    return inst;
}

sf::Texture& TextureManager::get(const std::string& path)
{
    auto it = cache_.find(path);
    if (it != cache_.end())
        return it->second;

    sf::Texture& tex = cache_[path];
    if (!tex.loadFromFile(path))
    {
        std::cerr << "[TextureManager] Failed to load: " << path << "\n";
        tex = fallback_;
    }
    tex.setSmooth(false);
    return tex;
}
