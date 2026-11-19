#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

class unordered_map;
namespace std
{
    class string;

}
struct SDL_Texture;

class ResourceManager
{
    public:
    ResourceManager(const char* filepath);
    ~ResourceManager();

    private:
    std::unordered_map<std::string, std::string> mLevelPaths;
    std::unordered_map<std::string, SDL_Texture*> mSprites;
    // audio files
};

#endif
