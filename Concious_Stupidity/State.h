#pragma once
#include <SFML/Graphics.hpp>

class State {
public:
	virtual void init() = 0;

	virtual void handleevent() = 0;
	virtual void update(float dt) = 0;
	virtual void render(float dt) = 0;

	virtual void Pause() {}
	virtual void Resume() {}
};