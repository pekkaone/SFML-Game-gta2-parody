#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Item.h"
#include "Engine.h"

enum PLAYER_ANIMATION_STATES {IDLE =0, MOVING, JUMPING, LANDING};

typedef std::unique_ptr<Item> ItemRef;

class MainCharacter {
public:
	MainCharacter(GameDataRef data);

	void init();

	sf::Sprite& getCharacterSprite();
	std::vector<ItemRef>& getInventory();
	void pushItemInventory(ItemRef&& itm);

	void initExistedItems();

	void moving(sf::View view);
	void SlotChange();
	void update();

	void render(sf::RenderTarget& target);

	void inventoryAction();
private:
	GameDataRef _data;

	sf::Sprite sprite;
	sf::IntRect spriteSheet;
	float Velocity;
	sf::Sound sound;

	int currentSlot = 0;
	std::vector<ItemRef> inventory;
};