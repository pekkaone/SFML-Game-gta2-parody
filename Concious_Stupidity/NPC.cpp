#include "NPC.h"

NPC::NPC(GameDataRef data, Car& car, Landscape& landscape)
	: _data(data),
	car1(car),
	land(landscape) {}

void NPC::init()
{
	_data->assets.loadTexture("NPCsprite", "Entities_Sprites/NPC.png");

	this->sprite.setTexture(_data->assets.GetTexture("NPCsprite"));
	this->sprite.setOrigin(sf::Vector2f(125.f, 125.f));
	this->sprite.setScale(0.4f, 0.4f);
	this->sprite.setPosition(1500, 1200);

	this->MCHitBox.setTexture(_data->assets.GetTexture("MainCHitbox"));
	this->MCHitBox.setOrigin(sf::Vector2f(125.f, 125.f));
	this->MCHitBox.setScale(0.3f, 0.3f);
	this->MCHitBox.setPosition(1500, 1200);

	Stuck = false;
	Velocity = 3.f;
}

void NPC::moving()
{
	moveDir = sf::Vector2f(0.f, 0.f);

	sf::Vector2f oldPos = sprite.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveDir.x -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveDir.x += 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moveDir.y += 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moveDir.y -= 1.f;
	}

	if (moveDir.x != 0.f || moveDir.y != 0.f) {
		float len = std::sqrt(moveDir.x * moveDir.x +
			moveDir.y * moveDir.y);
		moveDir /= len;
	};

	this->sprite.move(sf::Vector2f(moveDir.x * Velocity, 0.f));
	this->MCHitBox.setPosition(this->sprite.getPosition());

	//COLLISION
	if (this->car1.getHitbox().getRotation() == 0 && 90 && 180 && 270 && 360) {
		if (this->sprite.getGlobalBounds().intersects(car1.getHitbox().getGlobalBounds())) {
			this->sprite.setPosition(oldPos.x, sprite.getPosition().y);
		}
	}
	else {
		if (Collision::boundingBoxTest(sprite, car1.getCarSprite())) {
			if (Collision::pixelPerfectTest(sprite, car1.getCarSprite())) {
				this->sprite.setPosition(oldPos.x, sprite.getPosition().y);
			}
		}
	}

	this->sprite.move(sf::Vector2f(0.f, moveDir.y * Velocity));
	this->MCHitBox.setPosition(this->sprite.getPosition());

	if (this->car1.getHitbox().getRotation() == 0 && 90 && 180 && 270 && 360) {
		if (this->MCHitBox.getGlobalBounds().intersects(car1.getHitbox().getGlobalBounds())) {
			this->sprite.setPosition(sprite.getPosition().x, oldPos.y);
		}
	}
	else {
		if (Collision::boundingBoxTest(sprite, car1.getCarSprite())) {
			if (Collision::pixelPerfectTest(sprite, car1.getCarSprite())) {
				this->sprite.setPosition(sprite.getPosition().x, oldPos.y);
			}
		}
	}

	if (Collision::boundingBoxTest(sprite, car1.getCarSprite())) {
		if (Collision::pixelPerfectTest(sprite, car1.getCarSprite())) {
			int xPush = -10, yPush = -15;
			if (Stuck) {
				xPush *= -10;
				yPush *= -10;
			}
			this->sprite.move(xPush, yPush);
			Stuck = true;
		}
	}
	else {
		Stuck = false;
	}

	this->LandscapeCollision(oldPos);

	this->MCHitBox.setPosition(this->sprite.getPosition());
}

void NPC::LandscapeCollision(sf::Vector2f oldPos)
{
	for (auto home : land.GetInventory()) {
		if (this->sprite.getGlobalBounds().intersects(home.getSprite().getGlobalBounds())) {
			this->sprite.setPosition(oldPos);
		}
		if (Collision::boundingBoxTest(MCHitBox, home.sprite)) {
			this->sprite.move(100, 150);
		}
	};

}

void NPC::update()
{
	this->moving();
}

void NPC::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
