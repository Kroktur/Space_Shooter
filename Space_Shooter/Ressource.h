#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

class FontCache
{
public:
	sf::Font& getFont(const std::string& path);
	~FontCache();
private:
	struct Fontinfo {
		sf::Font* font;
		std::string path;
	};
	std::vector<Fontinfo> m_allFontInfos;
};