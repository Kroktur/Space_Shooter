#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class TextureCache
{
public:
	sf::Texture& getTexture(const std::string& path);
	~TextureCache();
private:
	struct TextureInfo {
		sf::Texture* texture;
		std::string path;
	};
	std::vector<TextureInfo> m_allTextureInfos;
};
