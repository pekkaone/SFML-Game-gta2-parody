#include "Item.h"
#include "MainCharacter.h"

Pistol::Pistol(GameDataRef data) : _data(data) {}

void Pistol::init()
{
	_data->assets.loadTexture("pistol1", "Entities_Sprites/gun-pistol1.png");
	item_number = 1;
	itemS.setTexture(_data->assets.GetTexture("pistol1"));
}

void Pistol::UpdateBullet()
{
	for (auto& bullet : bullets)
	{
		bullet.sprite.move(bullet.velocity);
	}
}

void Pistol::Shooting(sf::Sprite& hero)
{
	if (mousePressed != 0) {
		mousePressed -= 5;
	}
	else if (mousePressed <= 0) {
		mousePressed = 0;
	}

	sf::Vector2f mousePos;

	sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->_data->window);
	mousePos = _data->window->mapPixelToCoords(mousePixel);
	sf::Vector2f dir = mousePos - itemS.getPosition();
	direction = atan2(dir.y, dir.x) * 180 / 3.14f;

	this->itemS.setPosition(hero.getPosition().x + 50, hero.getPosition().y + 50);
	this->itemS.setRotation(direction);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed == 0) {
		mousePressed = 180;
		Bullet bullet;

		bullet.direction = itemS.getRotation();

		bullet.sprite.setSize(sf::Vector2f(70.f, 20.f));
		bullet.sprite.setPosition(this->itemS.getPosition());
		bullet.sprite.setRotation(bullet.direction);

		float radians = bullet.direction * 3.14159265f / 180.f;

		bullet.velocity.x = std::cos(radians) * 15.f;
		bullet.velocity.y = std::sin(radians) * 15.f;

		bullets.push_back(bullet);
	}
}

void Pistol::update(sf::Sprite& hero)
{
	Shooting(hero);
	UpdateBullet();
}

void Pistol::render()
{
	this->_data->window->draw(this->itemS);
	for (auto& x : bullets) {
		this->_data->window->draw(x.sprite);
	}
}