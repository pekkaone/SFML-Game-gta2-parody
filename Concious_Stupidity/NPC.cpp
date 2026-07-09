#include "NPC.h"

NPC::NPC(GameDataRef data, Car& car, Landscape& landscape, BulletConfig& BConfig)
	: _data(data),
	car1(car),
	land(landscape),
	BConfig(BConfig) {
	init();
}

void NPC::init()
{
	_data->assets.loadTexture("NPCsprite", "Entities_Sprites/NPC.png");
	_data->assets.loadTexture("NPCdead", "Entities_Sprites/NPCdead.png");

	this->sprite.setTexture(_data->assets.GetTexture("NPCsprite"));
	this->sprite.setOrigin(sf::Vector2f(125.f, 125.f));
	this->sprite.setScale(0.4f, 0.4f);
	this->sprite.setPosition(1500, 1200);

	this->MCHitBox.setTexture(_data->assets.GetTexture("MainCHitbox"));
	this->MCHitBox.setOrigin(sf::Vector2f(125.f, 125.f));
	this->MCHitBox.setScale(0.3f, 0.3f);
	this->MCHitBox.setPosition(1500, 1200);

	BeenGoingEnought = -100.f;

	Stuck = false;
	Velocity = 3.f;
	dead = false;
}
sf::Sprite& NPC::getCharacterSprite()
{
	return this->sprite;
}
/*
void NPC::moving()
{
	moveDir = sf::Vector2f(0.f, 0.f);

	//DIRECTION CHANGE
	if (BeenGoingEnought <= -100.f) {
		randomDirectionX = rand() % 9 - 4.f;
		randomDirectionY = rand() % 9 - 4.f;
		std::cout << "b";
		BeenGoingEnought = 200.f;
	}
	else if (BeenGoingEnought <= 0) {
		std::cout << "r";
		randomDirectionX = 0;
		randomDirectionY = 0;
	}

	sf::Vector2f oldPos = sprite.getPosition();

	moveDir.x += randomDirectionX;
	moveDir.y -= randomDirectionY;

	if (moveDir.x != 0.f || moveDir.y != 0.f) {
		float len = std::sqrt(moveDir.x * moveDir.x +
			moveDir.y * moveDir.y);
		moveDir /= len;
	};

	this->sprite.move(sf::Vector2f(moveDir.x * Velocity, 0.f));
	this->MCHitBox.setPosition(this->sprite.getPosition());
	BeenGoingEnought -= 1.f;

	if (moveDir.x != 0 || moveDir.y != 0) {
		side = 0.f;

		if (randomDirectionX == 0) {
			side += 180.f;
		}
		else if (randomDirectionX < 0) {
			side += 190.f;
		}
		else {
			side -= 190.f;
		}

		if (randomDirectionY == 0) {
			side -= 180.f;
		}
		else if (randomDirectionY < 0) {
			side += 190.f;
		}
		else {
			side -= 90.f;
		}

		angle = std::atan2(moveDir.y, moveDir.x) * side / 3.14159265f;
		sprite.setRotation(angle);
	}
	//COLLISION
	this->NPCCollision(oldPos);

	this->MCHitBox.setPosition(this->sprite.getPosition());
	std::cout << randomDirectionY << "\n";
	std::cout << randomDirectionX << "\n";
	std::cout << "side: " << side << "\n";
}
*/
void NPC::movingSimple(sf::Sprite BG)
{
	moveDir = sf::Vector2f(0.f, 0.f);

	//DIRECTION CHANGE
	if (BeenGoingEnought <= -100.f) {
		randomDirection = rand() % 9;
		BeenGoingEnought = 200.f;
	}
	else if (BeenGoingEnought <= 0) {
		randomDirectionX = 0;
		randomDirectionY = 0;
	}

	sf::Vector2f oldPos = sprite.getPosition();

	//UP DOWN RIGHT LEFT UP-LEFT UP-RIGHT DOWN-LEFT DOWN-RIGHT
	if (randomDirection == 1) {
		randomDirectionX = 0;
		randomDirectionY = 3;
		angle = 0;
	}
	else if (randomDirection == 2) {
		randomDirectionX = 0;
		randomDirectionY = -3;
		angle = 180;
	}
	else if (randomDirection == 3) {
		randomDirectionX = 3;
		randomDirectionY = 0;
		angle = 90;
	}
	else if (randomDirection == 4) {
		randomDirectionX = -3;
		randomDirectionY = 0;
		angle = -90;
	}
	else if (randomDirection == 5) {
		randomDirectionX = -3;
		randomDirectionY = 3;
		angle = -45;
	}
	else if (randomDirection == 6) {
		randomDirectionX = 3;
		randomDirectionY = 3;
		angle = 45;
	}
	else if (randomDirection == 7) {
		randomDirectionX = -3;
		randomDirectionY = -3;
		angle = -135;
	}
	else if (randomDirection == 8) {
		randomDirectionX = 3;
		randomDirectionY = -3;
		angle = 135;
	}

	moveDir.x += randomDirectionX;
	moveDir.y -= randomDirectionY;

	if (moveDir.x != 0.f || moveDir.y != 0.f) {
		float len = std::sqrt(moveDir.x * moveDir.x +
			moveDir.y * moveDir.y);
		moveDir /= len;
	};

	this->sprite.move(sf::Vector2f(moveDir.x * Velocity, 0.f));
	this->MCHitBox.setPosition(this->sprite.getPosition());
	BeenGoingEnought -= 1.f;
	sprite.setRotation(angle);

	//COLLISION
	this->NPCCollision(oldPos);
	this->MapBorders(oldPos, BG);

	this->MCHitBox.setPosition(this->sprite.getPosition());
}

bool& NPC::DeadStatus()
{
	return this->dead;
}

void NPC::NPCCollision(sf::Vector2f oldPos)
{
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
				HitByCar();
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

	for (auto home : land.GetInventory()) {
		if (this->sprite.getGlobalBounds().intersects(home.getSprite().getGlobalBounds())) {
			this->sprite.setPosition(oldPos);
		}
		if (Collision::boundingBoxTest(MCHitBox, home.sprite)) {
			this->sprite.move(100, 150);
		}
	};

}

void NPC::NPCtoNPCcolision(std::vector<NPC>& all_NPCs)
{
	for (int i = 0; i < all_NPCs.size(); i++) {
		if (Collision::circleTest(this->sprite, all_NPCs[i].getCharacterSprite())) {
			if (!all_NPCs[i].DeadStatus()) {
				float dx = this->sprite.getPosition().x - all_NPCs[i].getCharacterSprite().getPosition().x;
				float dy = this->sprite.getPosition().y - all_NPCs[i].getCharacterSprite().getPosition().y;

				float x = sprite.getPosition().x;
				float y = sprite.getPosition().y;
				sprite.setPosition(x += dx / 40, y += dx / 40);

				float xNPC = all_NPCs[i].getCharacterSprite().getPosition().x;
				float yNPC = all_NPCs[i].getCharacterSprite().getPosition().y;
				all_NPCs[i].getCharacterSprite().setPosition(xNPC -= dx / 10, yNPC -= dx / 10);
			}
		}
	}
}

void NPC::MapBorders(sf::Vector2f oldPos, sf::Sprite BG)
{
	if (this->sprite.getPosition().x + 0 > BG.getGlobalBounds().getSize().x)
	{
		sprite.setPosition(oldPos.x, sprite.getPosition().y);
	}
	if (this->sprite.getPosition().y + 0 > BG.getGlobalBounds().getSize().y)
	{
		sprite.setPosition(sprite.getPosition().x, oldPos.y);
	}
	if (this->sprite.getPosition().x - 0 < 200)
	{
		sprite.setPosition(oldPos.x, sprite.getPosition().y);
	}
	if (this->sprite.getPosition().y - 0 < 200)
	{
		sprite.setPosition(sprite.getPosition().x, oldPos.y);
	}
}

void NPC::HitByCar()
{
	if (!dead) {
		if (_data->PlayerState == 2) {
			this->sprite.setTexture(_data->assets.GetTexture("NPCdead"));
			this->sprite.setRotation(sprite.getRotation() - 90);
			this->sprite.setScale(0.7f, 0.7f);

			dead = true;
			_data->PointsNum += 1;
		}
	}
}

void NPC::HitByBullet()
{
	if (!dead) {
		for (auto bullet : BConfig.bullets) {
			if (this->sprite.getGlobalBounds().intersects(bullet.sprite.getGlobalBounds())) {
				this->sprite.setTexture(_data->assets.GetTexture("NPCdead"));
				this->sprite.setRotation(sprite.getRotation() - 90);
				this->sprite.setScale(0.7f, 0.7f);

				dead = true;
				_data->PointsNum += 1;
			}
		}
	}
}

void NPC::update(sf::Sprite BG)
{
	if (!dead) {
		this->movingSimple(BG);
		this->HitByBullet();
	}
}

void NPC::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
