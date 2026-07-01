#pragma once
#include "Engine.h"

class Bullet
{
public:
	Bullet(float rotation, sf::Vector2f ItemPos);

	void init();

	void Update();

	float direction;
	sf::RectangleShape sprite; //change that to normal sprite

	sf::Vector2f velocity;
};