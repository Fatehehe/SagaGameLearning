#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace saga{
    class AssetManager{
    protected:
        AssetManager();
    public:
        static AssetManager& Get();
    private:
        static unique<AssetManager> assetManager;
    };
}