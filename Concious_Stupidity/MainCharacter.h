#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Engine.h"

enum PLAYER_ANIMATION_STATES {IDLE =0, MOVING, JUMPING, LANDING};

class MainCharacter {
public:
	MainCharacter(GameDataRef data);

	void init();

	void moving(sf::View view);

	void update();

	void render(sf::RenderTarget& target);

	void inventoryAction();
private:
	GameDataRef _data;

	sf::Sprite sprite;
	sf::IntRect spriteSheet;
	float Velocity;
	sf::Sound sound;

	struct Item {
		GameDataRef data;
		Item(GameDataRef data) : data(data) {};
		MainCharacter* owner;

		float direction;
		int item_number;
		int slot_number;
		sf::Sprite itemS;
		void ItemAction();
		void renderItem(sf::RenderTarget& target);
	};
	int currentSlot = 0;
	std::vector<Item> inventory;

	sf::Sprite& getCharacterSprite();
};