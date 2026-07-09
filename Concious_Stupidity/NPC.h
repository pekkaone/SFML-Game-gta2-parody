#pragma once

#include "Engine.h"
#include "Collision.h"
#include "Car.h"
#include "Landscape.h"
#include "BulletsConfig.h"

class NPC {
public:
	NPC(GameDataRef data, Car& car1, Landscape& land, BulletConfig& BConfig);

	void init();

	sf::Sprite& getCharacterSprite();

	//void moving();
	void movingSimple(sf::Sprite BG);

	bool& DeadStatus();

	void NPCCollision(sf::Vector2f oldPos);
	void NPCtoNPCcolision(std::vector<NPC>& all_NPCs);
	void update(sf::Sprite BG);
	void MapBorders(sf::Vector2f oldPos, sf::Sprite BG);
	void HitByCar();
	void HitByBullet();

	void render(sf::RenderTarget& target);

	void CHARrotate();
private:
	GameDataRef _data;
	Car& car1;
	Landscape& land;
	BulletConfig& BConfig;

	float sprite_direction;
	sf::Sprite sprite;
	sf::Sprite MCHitBox;
	bool dead;

	//Moving
	float randomDirectionX;
	float randomDirectionY;
	float angle;
	float side;

	//Simple Moving
	int randomDirection;
	float Tox;
	float Toy;

	float BeenGoingEnought;
	bool Stuck;
	sf::Vector2f moveDir;
	float Velocity;
	sf::Sound sound;
};