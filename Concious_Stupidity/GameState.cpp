#include "GameState.h"

GameState::GameState(GameDataRef data) : _data(data), b(data) {}

void GameState::init()
{
	_data->assets.loadTexture("BG", "images/map.png");

	this->view.setSize(860, 600);
	this->view.setCenter(430, 300);

	BG.setTexture(_data->assets.GetTexture("BG"));
	b.init();
}

void GameState::handleevent()
{
	sf::Event ev;
	while (_data->window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) {
			_data->window->close();
		}
	}
}

void GameState::update(float dt)
{
	b.moving(view);
	b.update();
}

void GameState::renderBG()
{
	_data->window->draw(this->BG);
}

void GameState::render(float dt)
{
	renderBG();
	b.render(*this->_data->window);
}

