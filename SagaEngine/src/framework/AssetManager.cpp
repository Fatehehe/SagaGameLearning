#include "framework/AssetManager.h"
// #include "AssetManager.h"

namespace saga{
    unique<AssetManager> AssetManager::assetManager{nullptr};

    AssetManager::AssetManager()
    : mLoadedTextureMaps{}
    {

    }

    AssetManager& AssetManager::Get(){
    if(!assetManager){
            assetManager = unique<AssetManager>{new AssetManager()};
        }
        return *assetManager;
    }
    
    shared<sf::Texture> AssetManager::LoadTexture(const std::string &path)
    {
        auto found = mLoadedTextureMaps.find(path);
        if(found != mLoadedTextureMaps.end()){
            return found->second;
        }
        shared<sf::Texture> newTexture{new sf::Texture};
        if(newTexture->loadFromFile(path)){
            mLoadedTextureMaps.insert({path, newTexture});
            return newTexture;
        }

        return shared<sf::Texture>{nullptr};
    }
    
    void AssetManager::CleanCycle()
    {
        for(auto iter = mLoadedTextureMaps.begin(); iter != mLoadedTextureMaps.end();){
            if(iter->second.unique()){
                LOG("cleaning texture: %s", iter->first.c_str());
                iter = mLoadedTextureMaps.erase(iter);
            }else{
                ++iter;
            }
        }
    }
}
