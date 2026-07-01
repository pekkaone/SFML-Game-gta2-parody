#include "Item.h"
#include "MainCharacter.h"

Pistol::Pistol(GameDataRef data, BulletConfig& BConfig) : _data(data), Bconfig(BConfig) {}

void Pistol::init()
{
	_data->assets.loadTexture("pistol1", "Entities_Sprites/gun-pistol1.png");
	item_number = 1;
	itemS.setTexture(_data->assets.GetTexture("pistol1"));
	this->itemS.setOrigin(sf::Vector2f(0.f, -25.f));
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

	this->itemS.setPosition(hero.getPosition().x + 0, hero.getPosition().y + 0);
	this->itemS.setRotation(direction);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed == 0) {
		mousePressed = 180;
		float rot = itemS.getRotation();

		Bullet bullet(rot, this->itemS.getPosition());

		Bconfig.bullets.push_back(bullet);
	}
}

void Pistol::UpdateBullet()
{
	for (auto& x : bullets) {
		x.Update();
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

Arms::Arms(GameDataRef data) : _data(data) {}

void Arms::init()
{
	this->item_number = 0;
}

void Arms::UpdateBullet()
{
}

void Arms::Shooting(sf::Sprite& hero)
{
}

void Arms::update(sf::Sprite& hero)
{
	//nothing
}


void Arms::render()
{
	_data->window->draw(this->itemS);
}