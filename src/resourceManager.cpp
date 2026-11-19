#include "resourceManager.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <<nlohmann/json.hpp>

ResourceManager::ResourceManager(const char* filepath)
{
    std::ifstream file(filepath);

    nlohmann::json resources = nlohmann::json::parse(file);

    // get the levels
    for (const auto& [rawName, rawPath] : resources.at("levels").items()){

        std::string lvlName = rawName.get<std::string>();
        mLevelPaths[lvlName] = rawPath.get<std::string>();
    }

    // get the sprites
    for (const auto& [rawName, rawPath] : resources.at("sprites").items()){

        const char* path = rawPath.get<std::string>().c_str;
        SDL_Surface* surface = SDL_LoadBMP(path);

        mSprites[rawName.get<std::string>()] = SDL_CreateTextureFromSurface(surface);

        SDL_DestroySurface(surface);
    }

    // TODO audio files
}
