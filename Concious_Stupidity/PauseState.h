#pragma once
#include "State.h"
#include "Engine.h"

class PauseState : public State
{
public:
	PauseState(GameDataRef data);

	void init();
	void initResumeButton();
	void initSettingButton();
	void initLeaveButton();

	void handleevent();

	void MinusDelay();
	void updateButtonResume();
	void updateButtonSetting();
	void UpdateLeaveButton();
	void ResolutionApplier();
	void update(float dt);

	void RenderBG();
	void RenderResumeBt();
	void RenderSettingBt();
	void RenderLeaveButton();
	void render(float dt);
private:
	GameDataRef _data;

	sf::Text Title;
	sf::Vector2u textureSize;
	sf::Sprite BG;

	sf::Sprite ButtonResume;
	sf::IntRect RectResumeButton;

	sf::Sprite ButtonSetting;
	sf::IntRect RectSettingButton;

	sf::Sprite LeaveButton;

	float t = 0;
	sf::VideoMode target;

	float StatesDelay;
	sf::Mouse mouse;
	sf::Vector2f mousePos;
};
