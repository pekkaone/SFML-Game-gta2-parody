#pragma once
#include "State.h"
#include "Engine.h"

class SettingState : public State
{
public:
	SettingState(GameDataRef data);

	void init();
	void initBackButton();
	void initSoundChange();
	void initResolutionGui();

	void handleevent();

	void MinusDelay();
	void updateBackButton();
	void ResolutionChange();
	void UpdateSoundButton();
	void update(float dt);

	void RenderBackBut();
	void RenderSound();
	void RenderBG();
	void RenderResolutionGui();
	void render(float dt);
private:
	GameDataRef _data;

	sf::Text Title;
	sf::Vector2u textureSize;
	sf::Sprite BG;

	sf::Sprite BackButton;
	sf::IntRect RectBackButton;

	sf::Sprite SoundUp;
	sf::Sprite SoundDown;
	sf::Text SoundBar;

	std::vector<std::string> modes_str;
	int ElementIndex;
	bool Altered;
	sf::Sprite ResolutionChangeButton1;
	sf::Sprite ResolutionChangeButton2;
	sf::Text CurrentResolution;
	std::vector<sf::VideoMode> videomodes;

	bool Clicked;
	bool ResClicked;
	float t = 0;
	sf::VideoMode target;

	float StatesDelay;
	sf::Mouse mouse;
	sf::Vector2f mousePos;
};