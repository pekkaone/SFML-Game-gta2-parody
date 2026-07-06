#pragma once

#include "Landscape.h"
#include "State.h"
#include "Engine.h"
#include "MainCharacter.h"
#include "Car.h"
#include "BulletsConfig.h"
#include "NPC.h"
#include "NPC_Configurator.h"

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
	Car car1;
	Landscape landscape;
	BulletConfig BConfig;
	//NPC npc;
	NPC_Configurator npc_config;

	sf::Sprite BG;
	sf::View view;
};