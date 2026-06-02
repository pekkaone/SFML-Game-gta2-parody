#include "MainCharacter.h"

MainCharacter::MainCharacter(GameDataRef data) : _data(data) {}

void MainCharacter::init()
{
	_data->assets.loadTexture("MainC","Entities_Sprites/MainCharacter.png");
	_data->assets.loadTexture("pistol1", "Entities_Sprites/gun-pistol1.png");
	this->sprite.setTexture(_data->assets.GetTexture("MainC"));
	this->sprite.setScale(0.4f, 0.4f);

	currentSlot = 1;

	Item pistol(_data);
	pistol.owner = this;
	pistol.item_number = 1;
	pistol.itemS.setTexture(_data->assets.GetTexture("pistol1"));
	pistol.slot_number = inventory.size() + 1;
	this->inventory.push_back(pistol);

	Velocity = 3.f;
}

void MainCharacter::Item::ItemAction()
{
	sf::Vector2f mousePos;

	sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->data->window);
	mousePos = data->window->mapPixelToCoords(mousePixel);
	sf::Vector2f dir = mousePos - itemS.getPosition();
	direction = atan2(dir.y, dir.x) * 180 / 3.14f;

	this->itemS.setPosition(this->owner->sprite.getPosition().x + 50, this->owner->sprite.getPosition().y + 50);
	this->itemS.setRotation(direction);

	if (sf::Mouse::isButtonPressed) {
		sf::RectangleShape Bullet;
		Bullet.setSize(sf::Vector2f(70.f, 20.f));
		Bullet.setPosition(this->itemS.getPosition());

	}
}

void MainCharacter::Item::renderItem(sf::RenderTarget& target)
{
	this->data->window->draw(this->itemS);
}


void MainCharacter::moving(sf::View view)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->sprite.move(sf::Vector2f(-2.12f, -2.12f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->sprite.move(sf::Vector2f(2.12f, -2.12f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->sprite.move(sf::Vector2f(2.12f, 2.12f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->sprite.move(sf::Vector2f(-2.12f, 2.12f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->sprite.move(sf::Vector2f(-Velocity, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->sprite.move(sf::Vector2f(Velocity, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->sprite.move(sf::Vector2f(0.f, Velocity));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->sprite.move(sf::Vector2f(0.f, -Velocity));
	}

	view.setCenter(this->sprite.getPosition().x + 30, this->sprite.getPosition().y + 40);
	this->_data->window->setView(view);
}

sf::Sprite& MainCharacter::getCharacterSprite()
{
	return sprite;
}

void MainCharacter::inventoryAction()
{
	if (currentSlot == 0) {
		// Add arms
	}
	else if (currentSlot == 1) {
		this->inventory[0].ItemAction();
	}
}

void MainCharacter::update()
{
}

void MainCharacter::render(sf::RenderTarget& target)
{
	_data->window->draw(this->sprite);
	for (auto& item : inventory)
	{
		item.renderItem(target);
	}
}

