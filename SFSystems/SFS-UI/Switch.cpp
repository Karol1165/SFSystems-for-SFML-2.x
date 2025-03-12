#include "pch.h"
#include "Switch.hpp"

namespace SFS {
	//////////////////////////////////////////////////////////
	///Switch

	//Switch button

	void Switch::textSwitchButton::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->TextButton::CheckClick(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			if (this->buttonMode == mode::last) {
				this->owner->states.Last();
				this->owner->UpdateText();
			}
			else {
				this->owner->states.Next();
				this->owner->UpdateText();
			}
		}
	}

	void Switch::textSwitchButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		TextButton::draw(target, states);
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, float scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
		std::wstring string, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner) : TextButton(pos, mouseOut, mouseOn, scale, font, mouseOutText, mouseOnText,
			string, mouseEnteredSound, clickSound) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, sf::Texture& texture, float scale, sf::Font& font, textData textData, std::wstring string, mode buttonMode, Switch* owner) :
		TextButton(pos, texture, scale, font, textData, string) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, float scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
		std::wstring string, mode buttonMode, Switch* owner) : TextButton(pos, mouseOut, mouseOn, scale, font, mouseOutText, mouseOnText, string) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	sf::FloatRect Switch::textSwitchButton::getGlobalBounds() const {
		return this->buttonBackground.getGlobalBounds();
	}

	void Switch::imageSwitchButton::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->ImageButton::CheckClick(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			if (this->buttonMode == mode::last) {
				this->owner->states.Last();
				this->owner->UpdateText();
			}
			else {
				this->owner->states.Next();
				this->owner->UpdateText();
			}
		}
	}

	void Switch::imageSwitchButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		ImageButton::draw(target, states);
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, float buttonScale, sf::Texture& image, float iconScale, mode buttonMode, Switch* owner)
		: ImageButton(pos, mouseOut, mouseOn, buttonScale, image, iconScale) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, sf::Texture& texture, float buttonScale, sf::Texture& image, float iconScale, mode buttonMode, Switch* owner)
		: ImageButton(pos, texture, buttonScale, image, iconScale) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, float buttonScale, sf::Texture& image, float iconScale, sf::SoundBuffer& mouseEnteredSound,
		sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner) : ImageButton(pos, mouseOut,
			mouseOn, buttonScale, image, iconScale, mouseEnteredSound, clickSound) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	sf::FloatRect Switch::imageSwitchButton::getGlobalBounds() const {
		return this->buttonBackground.getGlobalBounds();
	}

	void Switch::UpdateText() {
		this->text.setString(this->states.getCurrentOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	void Switch::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(this->background, states);

		ClippedView<sf::Text> textView = ClippedView<sf::Text>(this->background.getGlobalBounds());
		textView.setObject(&text);
		target.draw(textView, states);

		target.draw(*this->leftButton, states);
		target.draw(*this->rightButton, states);


	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonMouseOutTex,
		sf::Texture& buttonMouseOnTex, float buttonScale, sf::Font& buttonFont, textData buttonMouseOutText, textData buttonMouseOnText, sf::SoundBuffer& buttonSpottedSound,
		sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText, std::wstring rightButtonText, SwitchStates states) {

		this->leftButton = ptr<baseSwitchButton>(new textSwitchButton(pos, buttonMouseOutTex, buttonMouseOnTex, buttonScale, buttonFont, buttonMouseOutText, buttonMouseOnText, leftButtonText, buttonSpottedSound,
			buttonClickSound, baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);



		this->rightButton = ptr<baseSwitchButton>(new textSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonMouseOutTex,
			buttonMouseOnTex, buttonScale, buttonFont, buttonMouseOutText, buttonMouseOnText, rightButtonText, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::next, this));



		this->text.setFont(textFont);
		setTextData(optionTextData, this->text);

		this->states = states;

		this->text.setString(this->states.getCurrentOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonTex, float buttonScale,
		sf::Font& buttonFont, textData buttonTextData, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText,
		std::wstring rightButtonText, SwitchStates states) {
		this->leftButton = ptr<baseSwitchButton>(new textSwitchButton(pos, buttonTex, buttonTex, buttonScale, buttonFont, buttonTextData, buttonTextData, leftButtonText, buttonSpottedSound, buttonClickSound, baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);

		this->rightButton = ptr<baseSwitchButton>(new textSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonTex,
			buttonTex, buttonScale, buttonFont, buttonTextData, buttonTextData, rightButtonText, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::next, this));

		this->text.setFont(textFont);
		setTextData(optionTextData, this->text);

		this->states = states;

		this->text.setString(this->states.getCurrentOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonMouseOutTex,
		sf::Texture& buttonMouseOnTex, float buttonScale, sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, float buttonIconScale, sf::SoundBuffer& buttonSpottedSound,
		sf::SoundBuffer& buttonClickSound, SwitchStates states) {

		this->leftButton = ptr<baseSwitchButton>(new imageSwitchButton(pos, buttonMouseOutTex, buttonMouseOnTex, buttonScale, leftButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);

		this->rightButton = ptr<baseSwitchButton>(new imageSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonMouseOutTex, buttonMouseOnTex,
			buttonScale, rightButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound, baseSwitchButton::mode::next, this));

		this->text.setFont(textFont);
		setTextData(optionTextData, this->text);

		this->states = states;

		this->text.setString(this->states.getCurrentOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonTex, float buttonScale,
		sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, float buttonIconScale, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, SwitchStates states) {

		this->leftButton = ptr<baseSwitchButton>(new imageSwitchButton(pos, buttonTex, buttonTex, buttonScale, leftButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);

		this->rightButton = ptr<baseSwitchButton>(new imageSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonTex, buttonTex, buttonScale,
			rightButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound, baseSwitchButton::mode::next, this));

		this->text.setFont(textFont);
		setTextData(optionTextData, this->text);

		this->states = states;

		this->text.setString(this->states.getCurrentOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	void Switch::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		this->leftButton->CheckStatus(e, deltaTime, mousePos);
		this->rightButton->CheckStatus(e, deltaTime, mousePos);
	}
}