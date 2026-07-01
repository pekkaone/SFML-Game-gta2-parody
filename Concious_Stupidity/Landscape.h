#pragma once

#include "Engine.h"
#include "Obstacle.h"

class Landscape
{
private:
	GameDataRef _data;

	struct LandOb : Obstacle
	{
		sf::Sprite sprite;
		sf::RectangleShape hitbox;

		void init();
		sf::RectangleShape& getHitbox();
		void update();
		void render();
		sf::Sprite& getSprite();

	};

	std::vector<LandOb> TrafficLights;

	std::vector<LandOb> homes;
public:
	Landscape(GameDataRef data);

	void init();
	void TrafficLighting();

	std::vector<LandOb>& GetInventory();
	sf::Sprite& SpecHomes(int num);
	void render();
};
