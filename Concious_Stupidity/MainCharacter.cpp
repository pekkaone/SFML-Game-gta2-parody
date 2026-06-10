#include "MainCharacter.h"

MainCharacter::MainCharacter(GameDataRef data) : _data(data) {}

void MainCharacter::init()
{
	_data->assets.loadTexture("MainC","Entities_Sprites/MainCharacter.png");
	this->sprite.setTexture(_data->assets.GetTexture("MainC"));
	this->sprite.setScale(0.4f, 0.4f);
	this->sprite.setOrigin(sf::Vector2f(50.f, 50.f));

	currentSlot = 1;

	Velocity = 3.f;

	initExistedItems();
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

	view.setCenter(this->sprite.getPosition().x + 40, this->sprite.getPosition().y + 30);
	this->_data->window->setView(view);
}

void MainCharacter::SlotChange()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		this->currentSlot = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		this->currentSlot = 1;
	}
}

sf::Sprite& MainCharacter::getCharacterSprite()
{
	return sprite;
}

std::vector<ItemRef>& MainCharacter::getInventory()
{
	return inventory;
}

void MainCharacter::pushItemInventory(ItemRef&& itm)
{
	inventory.push_back(std::move(itm));
}

void MainCharacter::initExistedItems()
{
	auto pistol = std::make_unique<Pistol>(_data);
	pistol->init();

	inventory.push_back(std::move(pistol));
}

void MainCharacter::inventoryAction()
{
	if (currentSlot == 0) {
		// Add arms
	}
	else if (currentSlot == 1) {
		this->inventory[0]->update(this->sprite);
	}
}

void MainCharacter::update()
{
	this->inventoryAction();
}

void MainCharacter::render(sf::RenderTarget& target)
{
	_data->window->draw(this->sprite);
	for (auto& item : inventory)
	{
		item->render();
	}
}