#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Car.h"
#include "Item.h"
#include "Engine.h"
#include "Collision.h"
#include "Landscape.h"
#include "BulletsConfig.h"

enum PLAYER_ANIMATION_STATES {IDLE =0, MOVING, JUMPING, LANDING};

typedef std::unique_ptr<Item> ItemRef;

class MainCharacter {
public:
	MainCharacter(GameDataRef data, Car& car1, Landscape& landscape, BulletConfig& BConfig);

	void init();

	sf::Sprite& getCharacterSprite();
	std::vector<ItemRef>& getInventory();
	void pushItemInventory(ItemRef&& itm);

	void initExistedItems();

	void moving(sf::View view);
	void SlotChange();
	void GetInCar();
	void SwitchBetState12(sf::Sprite exitPos);
	void LandscapeCollision(sf::Vector2f oldPos);
	void update();

	void render(sf::RenderTarget& target);

	void CHARrotate();
	void inventoryAction();
private:
	GameDataRef _data;
	BulletConfig& BConfig;
	Car& car1;
	Landscape& land;

	float sprite_direction;
	sf::Sprite sprite;
	sf::Sprite MCHitBox;
	sf::IntRect spriteSheet;

	bool Stuck;
	sf::Vector2f moveDir;
	float Velocity;
	sf::Sound sound;
	sf::Sound CarOpen;

	int currentSlot = 0;
	std::vector<ItemRef> inventory;
};