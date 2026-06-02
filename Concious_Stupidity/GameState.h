#pragma once

#include "State.h"
#include "Engine.h"
#include "MainCharacter.h"

class GameState : public State
{
public:
	GameState(GameDataRef data);

	void handleevent();

	void init();
	void update(float dt);

	void renderBG();
	void render(float dt);
private:
	GameDataRef _data;
	MainCharacter b;

	sf::Sprite BG;
	sf::View view;
	
	

};