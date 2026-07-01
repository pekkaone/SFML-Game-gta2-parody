#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
public:
	virtual ~Obstacle() = default;
	
	virtual void init() = 0;
	virtual sf::RectangleShape& getHitbox() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};