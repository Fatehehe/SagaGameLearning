#include "framework/AssetManager.h"

namespace saga{
    unique<AssetManager> AssetManager::assetManager{nullptr};

    AssetManager& AssetManager::Get(){
        if(!assetManager){
            assetManager = unique<AssetManager>{new AssetManager()};
        }
        return *assetManager;
    }
}