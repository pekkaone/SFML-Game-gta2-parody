#include "GameState.h"

GameState::GameState(GameDataRef data) 
	: _data(data), 
	landscape(data),
	car1(data, landscape), 
	BConfig(),
	//npc(data, car1, landscape, BConfig),
	npc_config(data, car1, landscape, BConfig),
	b(data, car1, landscape, BConfig) {}

void GameState::init()
{
	_data->assets.loadTexture("BG", "images/map.png");

	this->_data->view.setSize(1280, 720);
	this->_data->view.setCenter(4000, 400);

	BG.setTexture(_data->assets.GetTexture("BG"));
	b.init();
	car1.init();
	landscape.init();
	//npc.init();
	npc_config.SpawnNPCs();
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
	//npc.update();
	npc_config.UpdateNPCs();
	if (this->_data->PlayerState == 2) {
		car1.update(this->view, this->BG);
	}
	else if (this->_data->PlayerState == 1.5) {
		b.SwitchBetState12(car1.getCarSprite());
	}
	else {
		b.moving(this->view);
		b.update();
	}
	BConfig.BulletDelete(b.getCharacterSprite().getPosition());
	BConfig.UpdateBullets();
}

void GameState::renderBG()
{
	_data->window->draw(this->BG);
}

void GameState::render(float dt)
{
	renderBG();
	//npc.render(*_data->window);
	npc_config.RenderNPCs();
	car1.render();
	BConfig.RenderBullets(_data->window);
	if (this->_data->PlayerState == 1) {
		b.render(*this->_data->window);
	}
	landscape.render();
	
}

