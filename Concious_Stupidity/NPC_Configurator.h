#pragma once
#include "NPC.h"
#include "Engine.h"
#include "Collision.h"
#include "Car.h"
#include "Landscape.h"
#include "BulletsConfig.h"

class NPC_Configurator
{
public:
	NPC_Configurator(GameDataRef data, Car& car1, Landscape& land, BulletConfig& BConfig);
	
	void SpawnNPCs();
	void UpdateNPCs(sf::Sprite BG);
	void RenderNPCs();
	void RenderDeadNPCs();
	NPC& GetNPC(int num);

	std::vector<NPC> all_NPCs;
private:
	GameDataRef _data;
	Car& car1;
	Landscape& land;
	BulletConfig& BConfig;

};

