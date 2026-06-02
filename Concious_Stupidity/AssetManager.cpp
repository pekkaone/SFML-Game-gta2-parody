#include "AssetManager.h"


AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::loadTexture(std::string name, std::string fileName)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName))
	{
		this->_textures[name] = tex;
	}
}

sf::Texture& AssetManager::GetTexture(std::string name)
{
	auto it = this->_textures.find(name);

	if (it == this->_textures.end()) {
		throw std::runtime_error("Texture not found: " + name);
	}
	return this->_textures.at(name);
}

void AssetManager::loadFont(std::string name, std::string fileName)
{
	sf::Font font;
	if (font.loadFromFile(fileName))
	{
		this->_fonts[name] = font;
	}
}

sf::Font& AssetManager::GetFont(std::string name)
{
	return this->_fonts.at(name);
}

void AssetManager::loadSound(std::string name, std::string fileName)
{
	sf::SoundBuffer sound;
	if (sound.loadFromFile(fileName))
	{
		this->_sound[name] = sound;
	}
	else
	{
		std::cout << "PROBLEM HERE";
	}
}

sf::SoundBuffer& AssetManager::GetSound(std::string name)
{
	auto it = this->_sound.find(name);

	if (it == this->_sound.end())
	{
		throw std::runtime_error("sound not found");
	}

	return this->_sound.at(name);
}
