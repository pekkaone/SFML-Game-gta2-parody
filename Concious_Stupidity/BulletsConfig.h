#pragma once
#include "Bullets.h"

class BulletConfig
{
public:
	BulletConfig();

	void UpdateBullets();
	void RenderBullets(sf::RenderWindow* window);
	void BulletDelete(sf::Vector2f HeroPos);

	std::vector<Bullet> bullets;
private:

};