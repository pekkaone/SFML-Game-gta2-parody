#include "MainCharacter.h"

MainCharacter::MainCharacter(GameDataRef data, Car& car, Landscape& landscape, BulletConfig& BConfig) 
	: _data(data), 
	car1(car), 
	land(landscape),
	BConfig(BConfig) {}

void MainCharacter::init()
{
	_data->assets.loadTexture("MainC","Entities_Sprites/MainCharacter.png");
	_data->assets.loadTexture("MainCHitbox", "Entities_Sprites/MCHitbox.png");
	_data->assets.loadSound("DoorOpen", "Sounds/DFC.wav");

	this->sprite.setTexture(_data->assets.GetTexture("MainC"));
	this->sprite.setOrigin(sf::Vector2f(125.f, 125.f));
	this->sprite.setScale(0.4f, 0.4f);
	this->sprite.setPosition(1000, 1000);

	this->MCHitBox.setTexture(_data->assets.GetTexture("MainCHitbox"));
	this->MCHitBox.setOrigin(sf::Vector2f(125.f, 125.f));
	this->MCHitBox.setScale(0.3f, 0.3f);
	this->MCHitBox.setPosition(1000, 1000);
	Stuck = false;

	CarOpen.setBuffer(_data->assets.GetSound("DoorOpen"));

	currentSlot = 0;

	Velocity = 3.f;

	initExistedItems();
}

void MainCharacter::moving(sf::View view, sf::Sprite BG)
{
	moveDir = sf::Vector2f(0.f, 0.f);

	sf::Vector2f oldPos = sprite.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveDir.x -= 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveDir.x += 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		moveDir.y += 2.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		moveDir.y -= 2.f;
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
	this->ViewUpdate(view, BG);
}

void MainCharacter::ViewUpdate(sf::View view, sf::Sprite BG)
{
	sf::Vector2f oldView = _data->view.getCenter();

	_data->view.setCenter(this->sprite.getPosition().x + 0.f, this->sprite.getPosition().y + 0.f);

	if (this->sprite.getPosition().x + 640 > BG.getGlobalBounds().getSize().x)
	{
		_data->view.setCenter(oldView.x, _data->view.getCenter().y);
	}
	if (this->sprite.getPosition().y + 360 > BG.getGlobalBounds().getSize().y)
	{
		_data->view.setCenter(_data->view.getCenter().x, oldView.y);
	}
	if (this->sprite.getPosition().x - 0 < 640)
	{
		_data->view.setCenter(oldView.x, _data->view.getCenter().y);
	}
	if (this->sprite.getPosition().y - 0 < 360)
	{
		_data->view.setCenter(_data->view.getCenter().x, oldView.y);
	}
	_data->window->setView(_data->view);
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

void MainCharacter::initExistedItems()
{
	auto pistol = std::make_unique<Pistol>(_data, BConfig);
	auto arms = std::make_unique<Arms>(_data);
	pistol->init();
	arms->init();

	inventory.push_back(std::move(pistol));
	inventory.push_back(std::move(arms));
}

void MainCharacter::CHARrotate()
{
	sf::Vector2f mousePos;

	sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->_data->window);
	mousePos = _data->window->mapPixelToCoords(mousePixel);
	sf::Vector2f dir = mousePos - sprite.getPosition();
	sprite_direction = atan2(dir.y, dir.x) * 180 / 3.14f;

	this->sprite.setRotation(sprite_direction + 90);
}

void MainCharacter::inventoryAction()
{
	if (currentSlot == 0) {
		this->inventory[1]->update(this->sprite);
	}
	else if (currentSlot == 1) {
		this->inventory[0]->update(this->sprite);
	}
}

void MainCharacter::GetInCar()
{
	_data->E_Pressed -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && _data->E_Pressed <= 0) {
		if (this->sprite.getGlobalBounds().intersects(car1.getActionBox().getGlobalBounds())) {
			_data->PlayerState = 2;
			std::cout << "Entered the Car";
			_data->E_Pressed = 100;
			CarOpen.play();
		}
	}
}

void MainCharacter::SwitchBetState12(sf::Sprite exitPos)
{
	this->sprite.move(car1.getTrackingPTN());
	car1.resetGaga();
	_data->PlayerState = 1;
}

void MainCharacter::LandscapeCollision(sf::Vector2f oldPos)
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

void MainCharacter::NPCtoPlayer_Collisions(std::vector<NPC>& all_NPCs)
{
	for (int i = 0; i < all_NPCs.size(); i++) {
		if (Collision::circleTest(this->sprite, all_NPCs[i].getCharacterSprite())) {
			float dx = this->sprite.getPosition().x - all_NPCs[i].getCharacterSprite().getPosition().x;
			float dy = this->sprite.getPosition().y - all_NPCs[i].getCharacterSprite().getPosition().y;

			float x = sprite.getPosition().x;
			float y = sprite.getPosition().y;
			sprite.setPosition(x += dx / 70, y += dx / 70);

			float xNPC = all_NPCs[i].getCharacterSprite().getPosition().x;
			float yNPC = all_NPCs[i].getCharacterSprite().getPosition().y;
			all_NPCs[i].getCharacterSprite().setPosition(xNPC -= dx / 10, yNPC -= dx / 10);
		}
	}
}

void MainCharacter::update()
{
	this->CHARrotate();
	this->SlotChange();
	this->inventoryAction();
	this->GetInCar();
}

void MainCharacter::render(sf::RenderTarget& target)
{
	_data->window->draw(this->sprite);
	_data->window->draw(this->MCHitBox);
	if (currentSlot == 0) {
		this->inventory[1]->render();
	}
	else if (currentSlot == 1) {
		this->inventory[0]->render();
	}
}