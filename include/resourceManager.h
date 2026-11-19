#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <unordered_map>

struct SDL_Texture;
struct SDL_Renderer;

class ResourceManager
{
    public:
    ResourceManager(SDL_Renderer* renderer, const char* filepath);
    ~ResourceManager();

    private:
    std::unordered_map<std::string, std::string> mLevelPaths;
    std::unordered_map<std::string, SDL_Texture*> mSprites;
    // audio files
};

#endif
