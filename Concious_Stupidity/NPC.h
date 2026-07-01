#pragma once
#include "Engine.h"
#include "Collision.h"
#include "Car.h"
#include "Landscape.h"

class NPC {
public:
	NPC(GameDataRef data, Car& car1, Landscape& land);

	void init();

	sf::Sprite& getCharacterSprite();

	void moving();

	void LandscapeCollision(sf::Vector2f oldPos);
	void update();

	void render(sf::RenderTarget& target);

	void CHARrotate();
private:
	GameDataRef _data;
	Car car1; //We are having 2 different classes so collsion dont work // #FIX
	Landscape land;

	float sprite_direction;
	sf::Sprite sprite;
	sf::Sprite MCHitBox;

	bool Stuck;
	sf::Vector2f moveDir;
	float Velocity;
	sf::Sound sound;
};