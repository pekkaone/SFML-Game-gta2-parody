#include "Landscape.h"

Landscape::Landscape(GameDataRef data) : _data(data) {}

void Landscape::init()
{
	_data->assets.loadTexture("home", "images/home.png");
	_data->assets.loadTexture("TF", "images/TrafficLight.png");
	LandOb home;
	LandOb home2;
	LandOb home3;

	home.sprite.setTexture(_data->assets.GetTexture("home"));
	home.sprite.setPosition(1000, 50);
	home.sprite.setScale(1.4, 1.4);

	home2.sprite.setTexture(_data->assets.GetTexture("home"));
	home2.sprite.setPosition(1000, 1500);
	home2.sprite.setScale(1.4, 1.4);

	home3.sprite.setTexture(_data->assets.GetTexture("home"));
	home3.sprite.setPosition(3280, 1280);
	home3.sprite.setScale(1.1, 1.2);

	TrafficLighting();

	this->homes.push_back(home);
	this->homes.push_back(home2);
	this->homes.push_back(home3);
}

void Landscape::TrafficLighting()
{
	LandOb TrafficLight1, TrafficLight2, TrafficLight3, TrafficLight4, 
		   TrafficLight5, TrafficLight6, TrafficLight7, TrafficLight8;

	TrafficLights.push_back(TrafficLight1);
	TrafficLights.push_back(TrafficLight2);
	TrafficLights.push_back(TrafficLight3);
	TrafficLights.push_back(TrafficLight4);
	TrafficLights.push_back(TrafficLight5);
	TrafficLights.push_back(TrafficLight6);
	TrafficLights.push_back(TrafficLight7);
	TrafficLights.push_back(TrafficLight8);

	int i = 0;
	for (LandOb & x : TrafficLights) {
			x.sprite.setTexture(_data->assets.GetTexture("TF"));
			x.sprite.setScale(1.2f, 1.2f);
			x.sprite.setPosition(1200 + i, 900);
			i += 380;
	}

	for (auto x : TrafficLights) {
		homes.push_back(x);
	}
}


std::vector<Landscape::LandOb>& Landscape::GetInventory()
{
	return this->homes;
}

sf::Sprite& Landscape::SpecHomes(int num)
{
	return this->homes[num].getSprite();
}

void Landscape::render()
{
	for (auto home : homes)
	{
		_data->window->draw(home.getSprite());
	}
}

void Landscape::LandOb::init()
{
}

sf::RectangleShape& Landscape::LandOb::getHitbox()
{
	return this->hitbox;
}

void Landscape::LandOb::update()
{

}

void Landscape::LandOb::render()
{
}

sf::Sprite& Landscape::LandOb::getSprite()
{
	return this->sprite;
}
