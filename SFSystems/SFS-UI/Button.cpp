#include "pch.h"
#include "Button.hpp"

namespace SFS {
	/////////////////////////////////////////////////////////
	//BaseButton



	bool BaseButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
		bool isButtonClicked = false;
		if (this->buttonBackground.getGlobalBounds().contains(mousePos)) {
			BackgroundDataUpdate(true);

			if (isClicked) {
				this->clickSound.play();
				isButtonClicked = true;
			}
			if (!isMouseOn) {
				this->mouseEnteredSound.play();
			}
			this->isMouseOn = true;
		}
		else {
			this->isMouseOn = false;
			BackgroundDataUpdate(false);
		}
		return isButtonClicked;
	}


	void BaseButton::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->CheckClick(mousePos, e.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			//Do button function
			if (this->func)
				this->func();
		}
	}



	void BaseButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(buttonBackground);
	}

	void BaseButton::BackgroundDataUpdate(bool isSpotted) {
		if (isSpotted)
			setRectangleData(this->buttonBgrData.mouseOn, this->buttonBackground);
		else 
			setRectangleData(this->buttonBgrData.mouseOut, this->buttonBackground);
	}

	BaseButton::BaseButton(const sf::Vector2f& pos, const StyleData& style, buttonFunc func) {
		this->buttonBgrData.mouseOut = style.mouseOutBgrData;
		this->buttonBgrData.mouseOn = style.mouseOnBgrData;
		this->buttonBackground.setPosition(pos);
		setRectangleData(this->buttonBgrData.mouseOut, this->buttonBackground);
		this->func = func;
		setSoundData(style.mouseEnteredSoundData, this->mouseEnteredSound);
		setSoundData(style.clickSoundData, this->clickSound);
		this->isMouseOn = false;
	}

	/////////////////////////////////////////////////////
	//TextButton




	void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(buttonBackground);
		target.draw(textView);
	}


	bool TextButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
		bool isButtonClicked = false;
		if (this->buttonBackground.getGlobalBounds().contains(mousePos)) {
			this->buttonBackground.setTexture(this->buttonBgrData.mouseOn.texture);
			TextDataUpdate(true);
			BackgroundDataUpdate(true);
			if (isClicked) {
				this->clickSound.play();
				isButtonClicked = true;
			}
			if (!this->isMouseOn) {
				this->mouseEnteredSound.play();
			}
			this->isMouseOn = true;
		}
		else {
			this->isMouseOn = false;
			TextDataUpdate(false);
			BackgroundDataUpdate(false);
			this->buttonBackground.setTexture(this->buttonBgrData.mouseOut.texture);
		}
		return isButtonClicked;
	}

	void TextButton::TextDataUpdate(bool isSpotted) {
		if (isSpotted)
			setTextData(this->mouseOnTxtData, this->buttonText);
		else
			setTextData(this->mouseOutTxtData, this->buttonText);

		TextPosUpdate();
	}

	void TextButton::BackgroundDataUpdate(bool isSpotted) {
		BaseButton::BackgroundDataUpdate(isSpotted);
		TextPosUpdate();
		this->textView.setBounds(this->buttonBackground.getGlobalBounds());
	}


	void TextButton::TextInit(const textData& mouseOutText, const textData& mouseOnText) {
		this->mouseOutTxtData = mouseOutText;
		this->mouseOnTxtData = mouseOnText;
		TextDataUpdate();
		this->textView.setBounds(this->buttonBackground.getGlobalBounds());
		this->textView.setObject(&this->buttonText);
	}

	void TextButton::TextInit(const textData& mouseOutText, const textData& mouseOnText, const sf::String& string) {
		this->mouseOutTxtData = mouseOutText;
		this->mouseOnTxtData = mouseOnText;
		this->buttonText.setString(string);
		TextDataUpdate();
		this->textView.setBounds(this->buttonBackground.getGlobalBounds());
		this->textView.setObject(&this->buttonText);
	}


	TextButton::TextButton(const sf::Vector2f& pos, const StyleData& style, const sf::String& string,
		buttonFunc func) : BaseButton(pos, style, func) {
		this->TextInit(style.mouseOutTextData, style.mouseOnTextData, string);
	}

	TextButton::TextButton(const sf::Vector2f& pos, const StyleData& style, buttonFunc func) : BaseButton(pos, style, func) {
		this->TextInit(style.mouseOutTextData, style.mouseOnTextData);
	}




	////////////////////////////////////////////////////////
	//ImageButton



	void ImageButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(buttonBackground);
		target.draw(buttonImage);
	}

	void ImageButton::ImageInit(sf::Texture& image, float iconScale) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(iconScale, iconScale);
		this->ImagePosUpdate();
	}


	ImageButton::ImageButton(const sf::Vector2f& pos, const StyleData& style, sf::Texture& image, 
		buttonFunc func) : BaseButton(pos, style, func) {
		this->ImageInit(image, style.imageScale);
	}

	///////////////////////////////////////////////////////
	//CheckBox



	void CheckBox::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->CheckClick(mousePos, e.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			if (this->isChecked)
				this->isChecked = false;
			else
				this->isChecked = true;
			if (this->func)
				this->func();
		}
	}

	void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(this->buttonBackground, states);

		if (this->isChecked)
			target.draw(this->buttonImage, states);
	}

	CheckBox::CheckBox(const sf::Vector2f& pos, const StyleData& style,
		bool isChecked, buttonFunc whenStateChanges) : ImageButton(pos, style, *style.checkIcon, 
			whenStateChanges) {
		this->setState(isChecked);
	}

	//////////////////////////////////////////////////////////
	//RadioButton

	/*

	RadioButton::RadioButton(sf::Vector2f pos, sf::Texture& Tex, sf::Texture& activeTex, int butttonScale, buttonFunc whenStateChanges) : BaseButton(pos, Tex, activeTex,
		butttonScale, whenStateChanges) {
		isChecked = false;
	}

	RadioButton::RadioButton(sf::Vector2f pos, sf::Texture& Tex, sf::Texture& activeTex, int butttonScale, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, buttonFunc whenStateChanges) {
		isChecked = false;
	}

	void RadioButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		BaseButton::draw(target, states);
	}

	bool RadioButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
		bool isButtonClicked = false;
		if (buttonBackground.getGlobalBounds().contains(mousePos)) {
			buttonBackground.setTexture(buttonBgrData.mouseOn);

			if (isClicked) {
				clickSound.play();
				isButtonClicked = true;
			}
			if (!isMouseOn) {
				mouseEnteredSound.play();
			}
			isMouseOn = true;
		}
		else {
			isMouseOn = false;
			if (isChecked)
				buttonBackground.setTexture(buttonBgrData.mouseOn);
			else
				buttonBackground.setTexture(buttonBgrData.mouseOut);

		}
		return isButtonClicked;
	}

	void RadioButton::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->CheckClick(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			if (!this->isChecked)
				this->setActive();

			if (func != nullptr)
				func();
		}
	}

	void RadioButton::disableActive() {
		this->isChecked = false;
		this->buttonBackground.setTexture(this->buttonBgrData.mouseOut);
	}

	void RadioButton::setActive() {
		this->isChecked = true;
		this->buttonBackground.setTexture(this->buttonBgrData.mouseOn);


	}

	*/
}