#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace saga{
    class AssetManager{
    protected:
        AssetManager();
    public:
        static AssetManager& Get();
        shared<sf::Texture> LoadTexture(const std::string& path);
        void CleanCycle();
    private:
        static unique<AssetManager> assetManager;
        Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMaps;
        
    };
}