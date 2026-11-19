#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;

class ResourceManager
{
    public:
    ResourceManager(SDL_Renderer* renderer, const char* filepath);
    ~ResourceManager();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    // no copying resource manager
    // i don't foresee myself accidentally copying it but you can never be too safe

    std::string GetLevelPath(int levelNumber);

    private:
    std::vector<std::string> mLevelPaths;
    std::unordered_map<std::string, SDL_Texture*> mSprites;
    // audio files
};

#endif
