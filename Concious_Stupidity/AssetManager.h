#pragma once

#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	void loadTexture(std::string name, std::string fileName);
	sf::Texture& GetTexture(std::string name);

	void loadFont(std::string name, std::string fileName);
	sf::Font& GetFont(std::string name);

	void loadSound(std::string name, std::string fileName);
	sf::SoundBuffer& GetSound(std::string name);

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, sf::SoundBuffer> _sound;
};