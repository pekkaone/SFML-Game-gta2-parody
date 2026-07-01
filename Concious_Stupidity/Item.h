#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Engine.h"
#include "Bullets.h"
#include "BulletsConfig.h"

class Item {
public:
	virtual ~Item() = default;

	virtual void init() = 0;
	virtual void update(sf::Sprite& hero) = 0;
	virtual void render() = 0;
};

class Pistol : public Item
{
public:
	Pistol(GameDataRef data, BulletConfig& BConfig);

	void init();

	void update(sf::Sprite& hero);

	void render();
	void BulletRender();
private:
	GameDataRef _data;
	BulletConfig& Bconfig;

	float direction;
	int item_number;
	sf::Sprite itemS;

	void renderItem(sf::RenderTarget& target);
	void UpdateBullet();
	void Shooting(sf::Sprite& hero);

	float mousePressed = 0;

	std::vector<Bullet> bullets;
};

class Arms : public Item
{
public:
	Arms(GameDataRef data);

	void init();

	void update(sf::Sprite& hero);

	void render();
private:
	GameDataRef _data;

	float direction;
	int item_number;
	sf::Sprite itemS;

	void renderItem(sf::RenderTarget& target);
	void UpdateBullet();
	void Shooting(sf::Sprite& hero);
};

