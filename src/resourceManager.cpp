#include "resourceManager.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <SDL3/SDL.h>

ResourceManager::ResourceManager(SDL_Renderer* renderer, const char* filepath)
{
    std::ifstream file(filepath);

    nlohmann::json resources = nlohmann::json::parse(file);

    // get the levels
    for (const auto& [lvlName, lvlPath] : resources.at("levels").items()){
        mLevelPaths.push_back(lvlPath);
    }

    // get the sprites
    for (const auto& [spriteName, spriteData] : resources.at("sprites").items()){

        SpriteInfo info;

        std::string path = spriteData.at("path").get<std::string>();
        const char* spritePath = path.c_str();
        SDL_Surface* surface = SDL_LoadBMP(spritePath);

        info.texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_DestroySurface(surface);

        info.textureWidth = spriteData.at("textureDimensions").at("width");
        info.textureHeight = spriteData.at("textureDimensions").at("height");

        info.spriteWidth = spriteData.at("spriteDimensions").at("width");
        info.spriteHeight = spriteData.at("spriteDimensions").at("height");

        mSprites[spriteName] = info;
    }

    // TODO audio files
}

ResourceManager::~ResourceManager()
{
    for (const auto& [spriteName, info] : mSprites){

        SDL_DestroyTexture(info.texture);
    }
}

std::string ResourceManager::GetLevelPath(int levelNumber)
{
    return mLevelPaths[levelNumber];
}

SpriteInfo ResourceManager::GetTexture(std::string texture)
{
    return mSprites[texture];
}
