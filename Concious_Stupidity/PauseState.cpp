#include "PauseState.h"
#include "SettingState.h"

PauseState::PauseState(GameDataRef data) : _data(data) {}

void PauseState::init()
{
	_data->assets.loadTexture("BG_PauseState", "images/Pause_Backround.png");
	_data->assets.loadTexture("Resume", "images/ButtonResume.png");
	_data->assets.loadTexture("Setting", "images/SettingButton.png");
	_data->assets.loadTexture("Leave", "images/LeaveButton.png");
		
	this->_data->window->setView(_data->window->getDefaultView());

	BG.setTexture(_data->assets.GetTexture("BG_PauseState"));
	textureSize = _data->assets.GetTexture("BG_PauseState").getSize();
	StatesDelay = 150;

	Title.setFont(_data->assets.GetFont("Font1"));
	Title.setString("Pause");
	Title.setCharacterSize(90);
	Title.setPosition(560, 100);
	Title.setFillColor(sf::Color::Black);

	initSettingButton();
	initResumeButton();
	initLeaveButton();
}

void PauseState::initResumeButton()
{
	RectResumeButton = sf::IntRect(0, 0, 350, 200);
	ButtonResume.setTexture(_data->assets.GetTexture("Resume"));
	ButtonResume.setTextureRect(RectResumeButton);
	ButtonResume.setPosition(50.f, 360.f);
	ButtonResume.setScale(0.7f, 0.7f);
}

void PauseState::initSettingButton()
{
	RectSettingButton = sf::IntRect(0, 0, 350, 200);
	ButtonSetting.setTexture(_data->assets.GetTexture("Setting"));
	ButtonSetting.setTextureRect(RectSettingButton);
	ButtonSetting.setPosition(50.f, 510.f);
	ButtonSetting.setScale(0.7f, 0.7f);
}

void PauseState::initLeaveButton()
{
	LeaveButton.setTexture(_data->assets.GetTexture("Leave"));
	LeaveButton.setPosition(1000.f, 550.f);
	LeaveButton.setScale(0.6f, 0.6f);
}

void PauseState::handleevent()
{
	sf::Event ev;
	while (_data->window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed) {
			_data->window->close();
		}

		if (sf::Event::KeyPressed == ev.type) {
			if (sf::Keyboard::Escape == ev.key.code) {
				if (StatesDelay <= 0) {
					_data->machine.RemoveState();
				}
			}
		}

	}
}

void PauseState::MinusDelay()
{
	StatesDelay -= 1.5f;
}

void PauseState::updateButtonResume()
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->_data->window);
	mousePos = _data->window->mapPixelToCoords(mousePixel);

	if (this->ButtonResume.getGlobalBounds().contains(mousePos)) {
		this->RectResumeButton.top = 200;
		this->ButtonResume.setTextureRect(this->RectResumeButton);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_data->machine.RemoveState();
		}
	}
	else {
		this->RectResumeButton.top = 0;
		this->ButtonResume.setTextureRect(this->RectResumeButton);
	}
}

void PauseState::updateButtonSetting()
{
	if (this->ButtonSetting.getGlobalBounds().contains(mousePos)) {
		this->RectSettingButton.top = 200;
		this->ButtonSetting.setTextureRect(this->RectSettingButton);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_data->machine.AddState(StateRef(new SettingState(_data)), false);
		}
	}
	else {
		this->RectSettingButton.top = 0;
		this->ButtonSetting.setTextureRect(this->RectSettingButton);
	}
}

void PauseState::UpdateLeaveButton()
{
	if (this->LeaveButton.getGlobalBounds().contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->_data->window->close();
		}
	}
}

void PauseState::ResolutionApplier()
{
	float scaleX = static_cast<float>(_data->window->getSize().x) / textureSize.x;
	float scaleY = static_cast<float>(_data->window->getSize().y) / textureSize.y;
	BG.setScale(scaleX, scaleY);
}

void PauseState::update(float dt)
{
	ResolutionApplier();
	UpdateLeaveButton();
	updateButtonResume();
	updateButtonSetting();
	MinusDelay();
}

void PauseState::RenderBG()
{
	_data->window->draw(this->BG);
}

void PauseState::RenderResumeBt()
{
	_data->window->draw(this->ButtonResume);
}

void PauseState::RenderSettingBt()
{
	_data->window->draw(this->ButtonSetting);
}

void PauseState::RenderLeaveButton()
{
	_data->window->draw(this->LeaveButton);
}

void PauseState::render(float dt)
{
	RenderBG();
	RenderSettingBt();
	RenderResumeBt();
	RenderLeaveButton();
	_data->window->draw(Title);
}
