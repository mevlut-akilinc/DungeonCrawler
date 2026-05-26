#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager
{
public:
    static TextureManager& instance();

    sf::Texture& get(const std::string& path);

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

private:
    TextureManager() = default;

    std::unordered_map<std::string, sf::Texture> cache_;
    sf::Texture fallback_;
};
