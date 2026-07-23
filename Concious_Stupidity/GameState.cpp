#include "GameState.h"
#include "PauseState.h"
#include <sstream>

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
	_data->assets.loadFont("Font1", "Fonts/Yuyu-Regular.ttf");

	this->points.setPosition(0, 0);
	this->points.setFont(_data->assets.GetFont("Font1"));
	this->points.setCharacterSize(45);

	_data->PointsNum = 0;
	this->StatesDelay = 150.f;

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
		if (sf::Event::KeyPressed == ev.type) {
			if (sf::Keyboard::Escape == ev.key.code) {
				if (StatesDelay <= 0) {
					_data->machine.AddState(StateRef(new PauseState(_data)), false);
				}
			}
		}
	}
}


void GameState::MinusDelay()
{
	StatesDelay -= 1.5f;
}

void GameState::UpdatePoints()
{
	this->points.setPosition(_data->view.getCenter().x - 500, _data->view.getCenter().y - 350);
	this->points.setString("Killed: " + std::to_string(_data->PointsNum));
}

void GameState::update(float dt)
{
	//npc.update();
	npc_config.UpdateNPCs(BG);
	MinusDelay();
	if (this->_data->PlayerState == 2) {
		car1.update(this->view, this->BG);
	}
	else if (this->_data->PlayerState == 1.5) {
		b.SwitchBetState12(car1.getCarSprite());
	}
	else {
		b.moving(this->view, this->BG);
		b.update();
		b.NPCtoPlayer_Collisions(npc_config.all_NPCs);
	}

	BConfig.BulletDelete(b.getCharacterSprite().getPosition());
	BConfig.UpdateBullets();
	UpdatePoints();
}

void GameState::renderBG()
{
	_data->window->draw(this->BG);
}

void GameState::render(float dt)
{
	renderBG();
	//npc.render(*_data->window);
	npc_config.RenderDeadNPCs();
	npc_config.RenderNPCs();
	car1.render();
	BConfig.RenderBullets(_data->window);
	if (this->_data->PlayerState == 1) {
		b.render(*this->_data->window);
	}
	landscape.render();
	_data->window->draw(this->points);
}

