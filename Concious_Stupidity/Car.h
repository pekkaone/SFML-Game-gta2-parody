#pragma once
#include "Engine.h"
#include "Obstacle.h"
#include "Collision.h"
#include "Landscape.h"

class Car {
public:
	Car(GameDataRef data, Landscape& landscape);

	void init();
	sf::Sprite& getCarSprite();
	sf::RectangleShape& getActionBox();
	sf::Vector2f& getTrackingPTN();

	void resetGaga();
	void getOutofCar();
	//void ViewAnimation();
	sf::RectangleShape& getHitbox();
	void CarTracking();
	void Collisions(sf::Vector2f oldPos, float oldTurn);

	void update(sf::View view, sf::Sprite BG);

	void render();
private:
	GameDataRef _data;

	void CarSound();
	void carMovement(sf::View view, sf::Sprite BG);
	void ViewUpdate(sf::View view, sf::Sprite BG);

	sf::Sound CarClose;
	sf::Sound Honk;
	sf::Sound Driving;

	/*
	float ViewAnimationVar1;
	int ViewAnimationVar2;
	sf::View CarView;
	*/

	sf::Vector2f startPos;
	sf::Vector2f endPos;

	Landscape& land;

	bool started = false;
	bool finished = false;

	sf::Vector2f CarTrackingVector;

	sf::Sprite CarSprite;
	sf::RectangleShape hitBox;
	sf::RectangleShape ActionBox;

	float x, y;

	float speed;
	float max_speed;
	float acc, decc;
	float angle;
	float turnSpeed;

	bool up, down, left, right;
};