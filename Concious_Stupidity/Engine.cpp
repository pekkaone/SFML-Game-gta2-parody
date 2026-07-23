#include "Engine.h"
#include "GameState.h"

void Game_Engine::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = this->clock.getElapsedTime().asSeconds();
	float accumulator = 0.f;

	while (this->_data->window->isOpen())
	{
		this->_data->machine.ProcessStateChanges();

		newTime = this->clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		};

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->handleevent();
			this->_data->machine.GetActiveState()->update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->_data->window->clear();

		this->_data->machine.GetActiveState()->render(interpolation);

		this->_data->window->display();
	};
}

void Game_Engine::initWindow()
{
	std::ifstream ifs("Config/window.ini");
	this->VideoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds(1280, 720);
	bool FullScreen = false;
	unsigned framerate_limit = 60;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> FullScreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
		std::cout << window_bounds.width << window_bounds.height;
	}

	ifs.close();

	this->FullScreen = FullScreen;

	window_settings.antialiasingLevel = antialiasing_level;
	if (FullScreen) {
		_data->window = new sf::RenderWindow(sf::VideoMode(window_bounds), title, sf::Style::Fullscreen, window_settings);
	}
	else {
		_data->window = new sf::RenderWindow(sf::VideoMode(window_bounds), title, sf::Style::Titlebar | sf::Style::Close, window_settings);
	}
	
	_data->window->setFramerateLimit(framerate_limit);
	_data->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game_Engine::initVariables()
{
	_data->window = NULL;
	this->FullScreen = false;
}

Game_Engine::Game_Engine() {
	initWindow();
	_data->machine.AddState(StateRef(new GameState(_data)));
	this->Run();
}

