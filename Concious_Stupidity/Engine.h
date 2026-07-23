#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

#include "StateMachine.h"
#include "AssetManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class GameState;

struct GameData
{
	StateMachine machine;
	AssetManager assets;
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	float volume = 100;
	float PlayerState = 1; // 1 = normal, 2 = car, 1.5 switching from car to player
	float E_Pressed = 0;
	sf::View view;
	int PointsNum;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game_Engine
{
private:
	sf::VideoMode videomode;
	sf::ContextSettings window_settings;
	std::vector<sf::VideoMode> VideoModes;
	bool FullScreen;

	sf::Event ev;

	sf::Clock clock;
	const float dt = 1.f / 60.f;
	GameDataRef _data = std::make_shared<GameData>();

	void initWindow();
	void initVariables();
	void Run();

public:
	Game_Engine();
};