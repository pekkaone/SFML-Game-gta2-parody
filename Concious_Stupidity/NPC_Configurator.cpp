#include "NPC_Configurator.h"

NPC_Configurator::NPC_Configurator(GameDataRef data, Car& car, Landscape& landscape, BulletConfig& BConfig)
	: _data(data),
	car1(car),
	land(landscape),
	BConfig(BConfig) {
}

void NPC_Configurator::SpawnNPCs() // DO THIS ))))))))
{
	for (int i = 0; i < 50; i++) {
		all_NPCs.emplace_back(_data, car1, land, BConfig);
	}

	for (auto& x : all_NPCs) {
		float PlusX = 250 + rand() % 5000;
		float PlusY = 250 + rand() % 3500;
		x.getCharacterSprite().setPosition(PlusX, PlusY);
	}
}

void NPC_Configurator::UpdateNPCs(sf::Sprite BG)
{
	for (auto& x : all_NPCs) {
		if (!x.DeadStatus()) {
			x.NPCtoNPCcolision(this->all_NPCs);
			x.update(BG);
		}
	}
}

NPC& NPC_Configurator::GetNPC(int num)
{
	return this->all_NPCs[num];
}


void NPC_Configurator::RenderNPCs()
{
	for (auto& x : all_NPCs) {
		if (!x.DeadStatus()) {
			_data->window->draw(x.getCharacterSprite());
		}
	}
}

void NPC_Configurator::RenderDeadNPCs()
{
	for (auto& x : all_NPCs) {
		if (x.DeadStatus()) {
			_data->window->draw(x.getCharacterSprite());
		}
	}
}

