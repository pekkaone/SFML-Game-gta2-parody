#include "Car.h"

Car::Car(GameDataRef data, Landscape& landscape) : _data(data), land(landscape) {}

void Car::init()
{
	_data->assets.loadTexture("CAR1", "Entities_Sprites/Car.png");
	_data->assets.loadSound("honk", "Sounds/Honk.wav");
	_data->assets.loadSound("DC", "Sounds/DoorClose.wav");
	_data->assets.loadSound("drive", "Sounds/Drive3.wav");

	Honk.setBuffer(_data->assets.GetSound("honk"));
	Driving.setBuffer(_data->assets.GetSound("drive"));
	CarClose.setBuffer(_data->assets.GetSound("DC"));

	this->CarSprite.setTexture(_data->assets.GetTexture("CAR1"));
	this->CarSprite.setPosition(1200, 1100);
	this->CarSprite.setOrigin(sf::Vector2f(100.f, 125.f));

	this->hitBox.setPosition(1200, 1100);
	this->hitBox.setSize(sf::Vector2f(200.f, 350.f));
	this->hitBox.setOrigin(sf::Vector2f(100.f, 125.f));
	this->hitBox.setScale(1, 1);
	this->hitBox.setFillColor(sf::Color::Transparent);

	this->ActionBox.setPosition(1200, 1100);
	this->ActionBox.setSize(sf::Vector2f(200.f, 350.f));
	this->ActionBox.setOrigin(sf::Vector2f(100.f, 125.f));
	this->ActionBox.setScale(1.6f, 1.6f);
	this->ActionBox.setFillColor(sf::Color::Transparent);

	x = 1200;
	y = 1100;

	angle = 1.599f;
	speed = 0;
	max_speed = 15;
	acc = 0.2f;
	decc = 0.3f;
	turnSpeed = 0.08f;
	CarSprite.setRotation(angle * 180 / 3.141592);

	ActionBox.setPosition(this->CarSprite.getPosition());
	ActionBox.setRotation(this->CarSprite.getRotation());
	hitBox.setPosition(this->CarSprite.getPosition());
	hitBox.setRotation(this->CarSprite.getRotation());
}

sf::Sprite& Car::getCarSprite()
{
	return this->CarSprite;
}

sf::RectangleShape& Car::getActionBox()
{
	return this->ActionBox;
}

sf::Vector2f& Car::getTrackingPTN()
{
	return this->CarTrackingVector;
}

void Car::CarSound()
{
	if (this->speed >= 0) {
		this->Driving.setVolume(this->speed * _data->volume/100);
	}
	else if (this->speed < 0) {
		this->Driving.setVolume(this->speed * -1 * _data->volume / 100);
	}
	if (this->Driving.getStatus() == sf::Sound::Playing) {

	}
	else if (this->speed > 0) {
		this->Driving.play();
	}
	else if (this->speed < 0) {
		this->Driving.play();
	}
}

void Car::carMovement(sf::View view, sf::Sprite BG)
{
	sf::Vector2f oldPos = this->CarSprite.getPosition();
	float oldTurn = this->CarSprite.getRotation();

	up = 0, down = 0, left = 0, right = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->up = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->down = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->left = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->right = 1;
	}

	if (up && speed < max_speed)
		if (speed < 0) speed += decc;
		else {
			speed += acc;
		}

	if (down && speed > -max_speed)
		if (speed < 0) speed -= decc;
		else speed -= acc;

	if (!up && !down)
		if (speed - decc > 0) speed -= decc;
		else if (speed + decc < 0) speed += decc;
		else speed = 0;

	if (right && speed != 0) angle += turnSpeed * speed / max_speed;
	if (left && speed != 0) angle -= turnSpeed * speed / max_speed;

	x += sin(angle) * speed;
	
	y -= cos(angle) * speed;
	
	CarSprite.setRotation(angle * 180.f / 3.141592f);
	CarSprite.setPosition(x, CarSprite.getPosition().y);
	CarSprite.setPosition(CarSprite.getPosition().x, y);
	Collisions(oldPos, oldTurn);
	
	ActionBox.setPosition(this->CarSprite.getPosition());
	ActionBox.setRotation(this->CarSprite.getRotation());
	hitBox.setPosition(this->CarSprite.getPosition());
	hitBox.setRotation(this->CarSprite.getRotation());

	//view.setCenter(this->CarSprite.getPosition().x + 0.f, this->CarSprite.getPosition().y + 0.f);
	//_data->window->setView(view);

	this->ViewUpdate(_data->view, BG);
}

void Car::ViewUpdate(sf::View view, sf::Sprite BG)
{
	sf::Vector2f oldView = _data->view.getCenter();

	_data->view.setCenter(this->CarSprite.getPosition().x + 0.f, this->CarSprite.getPosition().y + 0.f);
	
	if (this->CarSprite.getPosition().x + 640 > BG.getGlobalBounds().getSize().x)
	{
		_data->view.setCenter(oldView.x, _data->view.getCenter().y);
	}
	if (this->CarSprite.getPosition().y + 360 > BG.getGlobalBounds().getSize().y)
	{
		_data->view.setCenter(_data->view.getCenter().x, oldView.y);
	}
	if (this->CarSprite.getPosition().x - 0 < 640)
	{
		_data->view.setCenter(oldView.x, _data->view.getCenter().y);
	}
	if (this->CarSprite.getPosition().y - 0 < 360)
	{
		_data->view.setCenter(_data->view.getCenter().x, oldView.y);
	}
	_data->window->setView(_data->view);
}

void Car::resetGaga()
{
	CarTrackingVector = sf::Vector2f(0.f, 0.f);
	started = false;
}

void Car::getOutofCar()
{
	_data->E_Pressed -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && _data->E_Pressed <= 0) {
		finished = true;
		started = false;
		_data->PlayerState = 1.5;
		_data->E_Pressed = 100;
		this->CarClose.setVolume(_data->volume);
		this->CarClose.play();
		speed = 0;
	}
}
sf::RectangleShape& Car::getHitbox()
{
	return this->hitBox;
}
void Car::CarTracking()
{
	if (!started) {
		startPos = this->CarSprite.getPosition();
	}
	else {
		endPos = this->CarSprite.getPosition();
	}
	CarTrackingVector = endPos - startPos;
}

void Car::Collisions(sf::Vector2f oldPos, float oldTurn)
{
	for (auto ob : land.GetInventory()) 
	{
		int dx = 0, dy = 0;
		if (this->hitBox.getGlobalBounds().intersects(ob.getSprite().getGlobalBounds()))
		{
			dx = x - ob.getSprite().getPosition().x;
			dy = y - ob.getSprite().getPosition().y;
			if (Collision::boundingBoxTest(this->CarSprite, ob.getSprite())) 
			{
				if (this->speed >= 0) {
					x += dx * speed / 85.0;
					y += dy * speed / 85.0;
					speed = speed * 0.3;
				}
				if (this->speed < 0) {
					x += -(dx * speed / 75.0);
					y += -(dy * speed / 75.0);
					speed = speed * 0.3;
				}
				//this->CarSprite.setPosition(oldPos);
				//this->CarSprite.setRotation(oldTurn);
			}
		}
	}
}

/*
void Car::ViewAnimation()
{
	for (int i = 0; i >= 40; i++) {
		ViewAnimationVar2 = 1.2;
		ViewAnimationVar1 = 2;
		ViewAnimationVar1 += ViewAnimationVar1;
		ViewAnimationVar2 += ViewAnimationVar2;
		CarView.setSize(1280 + ViewAnimationVar1, 720 + ViewAnimationVar2);
		_data->window->setView(CarView);
	}
	_data->window->setView(CarView);
}
*/

void Car::update(sf::View view, sf::Sprite BG)
{
	finished = false;
	this->carMovement(view, BG);
	this->CarTracking();
	this->getOutofCar();
	CarSound();
	started = true;
}

void Car::render()
{
	_data->window->draw(this->ActionBox);
	_data->window->draw(this->CarSprite);
	_data->window->draw(this->hitBox);
}


