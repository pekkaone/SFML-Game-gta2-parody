#include "BulletsConfig.h"

BulletConfig::BulletConfig() {}

void BulletConfig::UpdateBullets()
{
	for (auto& x : bullets) {
		x.Update();
	}
}

void BulletConfig::RenderBullets(sf::RenderWindow* window)
{
	for (auto& x : bullets) {
		window->draw(x.sprite);
	}
}

void BulletConfig::BulletDelete(sf::Vector2f HeroPos)
{
	for (int j = this->bullets.size() - 1; j >= 0; j--)
	{
		if (sqrt(pow((bullets[j].sprite.getPosition().x - HeroPos.x), 2) + pow((bullets[j].sprite.getPosition().y - HeroPos.y), 2)) > 600)
		{
			this->bullets.erase(bullets.begin() + j);
			break;
		}
	}
};
