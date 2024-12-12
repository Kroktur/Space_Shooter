#include "Ressource.h"

sf::Texture& TextureCache::getTexture(const std::string& path)
{
    for (auto& textureinfo : m_allTextureInfos)
    {
        if (textureinfo.path == path)
        {
            return *textureinfo.texture;
        }
    }
    TextureInfo ti;
    ti.path = path;
    ti.texture = new sf::Texture;
    ti.texture->loadFromFile(path);
    m_allTextureInfos.push_back(ti);

    return *ti.texture;
}

TextureCache::~TextureCache()
{
    for (auto textureinfo : m_allTextureInfos)
        delete textureinfo.texture;
    m_allTextureInfos.clear();
}
