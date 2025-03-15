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

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale,
		sf::Font& font, textData mouseOutText, textData mouseOnText, std::wstring string,
		const soundData& mouseEnteredSound, const soundData& clickSound, mode buttonMode, Switch* owner) : TextButton(pos, mouseOut, mouseOn, scale, font, mouseOutText, mouseOnText,
			string, mouseEnteredSound, clickSound) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, const rectangleShapeData& data, float scale,
		sf::Font& font, textData textData, std::wstring string, mode buttonMode, Switch* owner) :
		TextButton(pos, data, scale, font, textData, string) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
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

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale,
		sf::Texture& image, float iconScale, mode buttonMode, Switch* owner)
		: ImageButton(pos, mouseOut, mouseOn, buttonScale, image, iconScale) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, const rectangleShapeData& data, float buttonScale,
		sf::Texture& image, float iconScale, mode buttonMode, Switch* owner)
		: ImageButton(pos, data, buttonScale, image, iconScale) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale,
		sf::Texture& image, float iconScale, const soundData& mouseEnteredSound,
		const soundData& clickSound, mode buttonMode, Switch* owner) : ImageButton(pos, mouseOut,
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

	void Switch::optionTextInit(const SwitchStates& states, const sf::Font& font, const textData& data) {
		this->states = states;
		this->text.setFont(font);
		setTextData(data, this->text);
		this->textView.setObject(&this->text);
		this->textView.setBounds(this->background.getGlobalBounds());
		this->UpdateText();
	}

	void Switch::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(this->background, states);

		target.draw(this->textView, states);

		target.draw(*this->leftButton, states);
		target.draw(*this->rightButton, states);


	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, const rectangleShapeData& buttonMouseOut,
		const rectangleShapeData& buttonMouseOn, float buttonScale, sf::Font& buttonFont, textData buttonMouseOutText, textData buttonMouseOnText, const soundData& buttonSpottedSound,
		const soundData& buttonClickSound, std::wstring leftButtonText, std::wstring rightButtonText, SwitchStates states) {

		this->leftButton = ptr<baseSwitchButton>(new textSwitchButton(pos, buttonMouseOut, buttonMouseOn, buttonScale, buttonFont, buttonMouseOutText, buttonMouseOnText, leftButtonText, buttonSpottedSound,
			buttonClickSound, baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);



		this->rightButton = ptr<baseSwitchButton>(new textSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonMouseOut,
			buttonMouseOn, buttonScale, buttonFont, buttonMouseOutText, buttonMouseOnText, rightButtonText, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::next, this));


		this->optionTextInit(states, textFont, optionTextData);
	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, const rectangleShapeData& buttonData, float buttonScale,
		sf::Font& buttonFont, textData buttonTextData, std::wstring leftButtonText,
		std::wstring rightButtonText, SwitchStates states) {
		this->leftButton = ptr<baseSwitchButton>(new textSwitchButton(pos, buttonData, buttonData, buttonScale, buttonFont, buttonTextData, buttonTextData, leftButtonText, baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);

		this->rightButton = ptr<baseSwitchButton>(new textSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonData,
			buttonData, buttonScale, buttonFont, buttonTextData, buttonTextData, rightButtonText,
			baseSwitchButton::mode::next, this));

		this->optionTextInit(states, textFont, optionTextData);
	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, const rectangleShapeData& buttonMouseOut,
		const rectangleShapeData& buttonMouseOn, float buttonScale, sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, float buttonIconScale, const soundData& buttonSpottedSound,
		const soundData& buttonClickSound, SwitchStates states) {

		this->leftButton = ptr<baseSwitchButton>(new imageSwitchButton(pos, buttonMouseOut, buttonMouseOn, buttonScale, leftButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);

		this->rightButton = ptr<baseSwitchButton>(new imageSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonMouseOut, buttonMouseOn,
			buttonScale, rightButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound, baseSwitchButton::mode::next, this));

		this->optionTextInit(states, textFont, optionTextData);
	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, const rectangleShapeData& buttonData, float buttonScale,
		sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, float buttonIconScale, SwitchStates states) {

		this->leftButton = ptr<baseSwitchButton>(new imageSwitchButton(pos, buttonData, buttonData, buttonScale, leftButtonImage, buttonIconScale,
			baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);

		this->rightButton = ptr<baseSwitchButton>(new imageSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonData, buttonData, buttonScale,
			rightButtonImage, buttonIconScale, baseSwitchButton::mode::next, this));

		this->optionTextInit(states, textFont, optionTextData);
	}

	void Switch::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		this->leftButton->CheckStatus(e, deltaTime, mousePos);
		this->rightButton->CheckStatus(e, deltaTime, mousePos);
	}
}