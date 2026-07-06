#include "NPC_Configurator.h"

NPC_Configurator::NPC_Configurator(GameDataRef data, Car& car, Landscape& landscape, BulletConfig& BConfig)
	: _data(data),
	car1(car),
	land(landscape),
	BConfig(BConfig) {
}

void NPC_Configurator::SpawnNPCs() // DO THIS ))))))))
{
	for (int i = 0; i < 10; i++) {
		all_NPCs.emplace_back(_data, car1, land, BConfig);
	}

	int b = 0;
	for (auto& x : all_NPCs) {
		x.getCharacterSprite().setPosition(1500 + b, 1200);
		b += 380;
	}
}

void NPC_Configurator::UpdateNPCs()
{
	for (auto& x : all_NPCs) {
		x.update();
		std::cout << x.getCharacterSprite().getPosition().x << " " << x.getCharacterSprite().getPosition().y << "\n";
	}
	std::cout << "NPCs : " << all_NPCs.size() << "\n";
}

void NPC_Configurator::RenderNPCs()
{
	for (auto& x : all_NPCs) {
		_data->window->draw(x.getCharacterSprite());
	}
}
