#include "Bullets.h"

Bullet::Bullet(float rotation, sf::Vector2f ItemPos)
{
	this->direction = rotation;

	sprite.setOrigin(sf::Vector2f(-65.f, -27.f));
	sprite.setSize(sf::Vector2f(70.f, 20.f));
	sprite.setPosition(ItemPos);
	sprite.setRotation(this->direction);

	float radians = this->direction * 3.14159265f / 180.f;

	velocity.x = std::cos(radians) * 15.f;
	velocity.y = std::sin(radians) * 15.f;
}

void Bullet::init()
{
}

void Bullet::Update()
{
	this->sprite.move(velocity);

}