#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;

struct SpriteInfo
{
    SDL_Texture* texture;
    int textureWidth;
    int textureHeight;
    int spriteWidth;
    int spriteHeight;
}

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
    TextureInfo GetTexture(std::string texture);

    private:
    std::vector<std::string> mLevelPaths;
    std::unordered_map<std::string, TextureInfo> mSprites;
    // audio files
};

#endif
