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

	Switch::textSwitchButton::textSwitchButton(const sf::Vector2f& pos, const TextButton::StyleData& style, const sf::String& string,
		 mode buttonMode, Switch* owner) : TextButton(pos, style, string) {
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

	Switch::imageSwitchButton::imageSwitchButton(const sf::Vector2f& pos, const ImageButton::StyleData& style,
		sf::Texture& image, mode buttonMode, Switch* owner)
		: ImageButton(pos, style, image) {
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

	void Switch::optionTextInit(const SwitchStates& states, const textData& data) {
		this->states = states;
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

	Switch::Switch(const sf::Vector2f& pos, const rectangleShapeData& backgroundData, const textData& optionTextData, 
		const TextButton::StyleData& btnStyle,
		const sf::String& leftButtonText, const sf::String& rightButtonText, SwitchStates states) {

		this->leftButton = sptr<baseSwitchButton>(new textSwitchButton(pos, btnStyle, leftButtonText, baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);

		this->rightButton = sptr<baseSwitchButton>(new textSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y),
			btnStyle, rightButtonText, baseSwitchButton::mode::next, this));


		this->optionTextInit(states, optionTextData);
	}

	Switch::Switch(const sf::Vector2f& pos, const rectangleShapeData& backgroundData, const textData& optionTextData,
		const ImageButton::StyleData& btnStyle, 
		sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, SwitchStates states) {

		this->leftButton = sptr<baseSwitchButton>(new imageSwitchButton(pos, btnStyle, leftButtonImage, baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		setRectangleData(backgroundData, this->background);

		this->rightButton = sptr<baseSwitchButton>(new imageSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y),
			btnStyle, rightButtonImage, baseSwitchButton::mode::next, this));

		this->optionTextInit(states, optionTextData);
	}

	void Switch::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		this->leftButton->CheckStatus(e, deltaTime, mousePos);
		this->rightButton->CheckStatus(e, deltaTime, mousePos);
	}
}