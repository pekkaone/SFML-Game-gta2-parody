#include "SettingState.h"

SettingState::SettingState(GameDataRef data) : _data(data) {}

void SettingState::init()
{
	_data->assets.loadTexture("BackButton", "images/BackButton.png");
	_data->assets.loadTexture("SoundUps", "images/SoundUp.png");
	_data->assets.loadTexture("SoundDowns", "images/SoundDown.png");

	this->_data->window->setView(_data->window->getDefaultView());

	BG.setTexture(_data->assets.GetTexture("BG_PauseState"));
	textureSize = _data->assets.GetTexture("BG_PauseState").getSize();
	
	Title.setFont(_data->assets.GetFont("Font1"));
	Title.setString("Setting");
	Title.setCharacterSize(90);
	Title.setPosition(545, 100);
	Title.setFillColor(sf::Color::Black);
	
	StatesDelay = 150;
	this->Clicked = false;
	this->Altered = false;

	this->videomodes = sf::VideoMode::getFullscreenModes();

	initBackButton();
	initSoundChange();
	initResolutionGui();
}

void SettingState::initBackButton()
{
	RectBackButton = sf::IntRect(0, 0, 350, 200);
	BackButton.setTexture(_data->assets.GetTexture("BackButton"));
	BackButton.setTextureRect(RectBackButton);
	BackButton.setPosition(50.f, 50.f);
	BackButton.setScale(0.7f, 0.7f);
}

void SettingState::initSoundChange()
{
	this->SoundUp.setTexture(_data->assets.GetTexture("SoundUps"));
	this->SoundUp.setPosition(100, 500);
	this->SoundDown.setTexture(_data->assets.GetTexture("SoundDowns"));
	this->SoundDown.setPosition(350, 500);

	this->SoundBar.setFont(_data->assets.GetFont("Font1"));
	this->SoundBar.setString("Volume: " + std::to_string(_data->volume));
	this->SoundBar.setPosition(220, 500);
}

void SettingState::initResolutionGui()
{
	this->CurrentResolution.setString(
		"Resolution: " + std::to_string(_data->window->getSize().x) + "  " + std::to_string(_data->window->getSize().y));
	this->CurrentResolution.setFont(_data->assets.GetFont("Font1"));
	this->CurrentResolution.setCharacterSize(60);
	this->CurrentResolution.setPosition(180, 370);
	this->CurrentResolution.setFillColor(sf::Color::Black);

	this->ResolutionChangeButton1.setTexture(_data->assets.GetTexture("SoundDowns"));
	this->ResolutionChangeButton1.setPosition(600, 370);

	this->ResolutionChangeButton2.setTexture(_data->assets.GetTexture("SoundUps"));
	this->ResolutionChangeButton2.setPosition(50, 370);

	for (auto& i : this->videomodes) {
		this->modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}

	ElementIndex = 15;
	for (auto x : modes_str) {
		std::cout << "\n" + x ;
	}
}

void SettingState::handleevent()
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

void SettingState::MinusDelay()
{
	StatesDelay -= 1.5f;
}

void SettingState::updateBackButton()
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition(*this->_data->window);
	mousePos = _data->window->mapPixelToCoords(mousePixel);

	if (this->BackButton.getGlobalBounds().contains(mousePos)) {
		this->RectBackButton.top = 200;
		this->BackButton.setTextureRect(this->RectBackButton);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_data->machine.RemoveState();
		}
	}
	else {
		this->RectBackButton.top = 0;
		this->BackButton.setTextureRect(this->RectBackButton);
	}
}

void SettingState::ResolutionChange()
{
	Altered = false;
	if (this->ResolutionChangeButton1.getGlobalBounds().contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!ResClicked) {
				ResClicked = true;
				if (videomodes.size() - 1 > ElementIndex && ElementIndex >= 1) {
					ElementIndex += 1;
				}
				Altered = true;
			}
		}
	}
	else if (this->ResolutionChangeButton2.getGlobalBounds().contains(mousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!ResClicked) {
				ResClicked = true;
				if (videomodes.size() > ElementIndex && ElementIndex >= 1) {
					ElementIndex -= 1;
				}
				Altered = true;
			}
		}
	}
	else {
		ResClicked = false;
	}

	std::cout << ElementIndex;

	if (videomodes.size() >= ElementIndex && ElementIndex >= 1) {
		target = videomodes[ElementIndex];
	}
	auto it = std::find(videomodes.begin(), videomodes.end(), target);

	if (ElementIndex >= 1 && ElementIndex < videomodes.size()) {
		if (this->Altered == true) {
			_data->window->create(this->videomodes[ElementIndex], "Concious Stupidity", sf::Style::Default);
		}
	}

	if (it != videomodes.end()) {
		this->CurrentResolution.setString(modes_str[ElementIndex]);
	}
	
	float scaleX = static_cast<float>(_data->window->getSize().x) / textureSize.x;
	float scaleY = static_cast<float>(_data->window->getSize().y) / textureSize.y;
	BG.setScale(scaleX, scaleY);
}

void SettingState::UpdateSoundButton()
{
	if (this->SoundUp.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (_data->volume > 0) {
			if (!Clicked) {
				Clicked = true;
				_data->volume -= 10;
			}
		}
	}
	else if (this->SoundDown.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (_data->volume < 100) {
			if (!Clicked) {
				Clicked = true;
				_data->volume += 10;
			}
		}
	}
	else {
		this->Clicked = false;
	}

	this->SoundBar.setString("Volume: " + std::to_string(static_cast<int>(_data->volume)));
}

void SettingState::update(float dt)
{
	ResolutionChange();
	MinusDelay();
	UpdateSoundButton();
	updateBackButton();
}

void SettingState::RenderBackBut()
{
	_data->window->draw(this->BackButton);
}

void SettingState::RenderSound()
{
	_data->window->draw(this->SoundBar);
	_data->window->draw(this->SoundUp);
	_data->window->draw(this->SoundDown);
}

void SettingState::RenderBG()
{
	_data->window->draw(this->BG);
}

void SettingState::RenderResolutionGui()
{
	_data->window->draw(this->CurrentResolution);
	_data->window->draw(this->ResolutionChangeButton1);
	_data->window->draw(this->ResolutionChangeButton2);
}

void SettingState::render(float dt)
{
	RenderBG();
	RenderBackBut();
	RenderSound();
	RenderResolutionGui();
	_data->window->draw(Title);
}
