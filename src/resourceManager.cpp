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
    for (const auto& [spriteName, rawPath] : resources.at("sprites").items()){

        std::string path =rawPath.get<std::string>();
        const char* spritePath = path.c_str();
        SDL_Surface* surface = SDL_LoadBMP(spritePath);

        mSprites[spriteName] = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_DestroySurface(surface);
    }

    // TODO audio files
}

ResourceManager::~ResourceManager()
{
    for (const auto& [spriteName, spriteTexture] : mSprites){

        SDL_DestroyTexture(spriteTexture);
    }
}
