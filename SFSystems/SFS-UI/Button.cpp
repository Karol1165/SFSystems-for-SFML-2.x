#include "pch.h"
#include "Button.hpp"

namespace SFS {
	/////////////////////////////////////////////////////////
	//BaseButton



	bool BaseButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
		bool isButtonClicked = false;
		if (this->buttonBackground.getGlobalBounds().contains(mousePos)) {
			this->buttonBackground.setTexture(this->buttonBgrData.mouseOn.texture);

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
			this->buttonBackground.setTexture(buttonBgrData.mouseOut.texture);
		}
		return isButtonClicked;
	}


	void BaseButton::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->CheckClick(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			//Do button function
			if (this->func != nullptr)
				this->func();
		}
	}



	void BaseButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(buttonBackground);
	}


	BaseButton::BaseButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, buttonFunc func) {
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		setRectangleData(this->buttonBgrData.mouseOut, this->buttonBackground);
		this->func = func;
		this->isMouseOn = false;
	}


	BaseButton::BaseButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, buttonFunc func, sf::SoundBuffer& mouseEnteredSound,
		sf::SoundBuffer& clickSound) {
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		setRectangleData(this->buttonBgrData.mouseOut, this->buttonBackground);
		this->func = func;
		this->mouseEnteredSound.setBuffer(mouseEnteredSound);
		this->clickSound.setBuffer(clickSound);
		this->mouseEnteredSound.setVolume(100);
		this->clickSound.setVolume(100);
		this->isMouseOn = false;
	}

	/////////////////////////////////////////////////////
	//TextButton




	void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(buttonBackground);
		ClippedView<sf::Text> textView = ClippedView<sf::Text>(buttonBackground.getGlobalBounds());
		textView.setObject(&buttonText);
		target.draw(textView);
	}


	bool TextButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
		bool isButtonClicked = false;
		if (this->buttonBackground.getGlobalBounds().contains(mousePos)) {
			this->buttonBackground.setTexture(this->buttonBgrData.mouseOn.texture);
			TextDataUpdate(true);
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
			this->buttonBackground.setTexture(this->buttonBgrData.mouseOut.texture);
		}
		return isButtonClicked;
	}


	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, sf::Font& font,
		const textData& mouseOutText, const textData& mouseOnText, std::wstring string,
		buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func) {
		this->mouseOutTxtData = mouseOutText;
		this->mouseOnTxtData = mouseOnText;
		this->buttonText.setFont(font);
		this->buttonText.setString(string);
		TextDataUpdate();
	}



	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, sf::Font& font,
		const textData& mouseOutText, const textData& mouseOnText,
		buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func) {
		this->mouseOutTxtData = mouseOutText;
		this->mouseOnTxtData = mouseOnText;
		this->buttonText.setFont(font);
		TextDataUpdate();
	}


	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& data, float scale, sf::Font& font,
		const textData& textData, std::wstring string, buttonFunc func)
		: BaseButton(pos, data, data, scale, func) {
		this->mouseOutTxtData = textData;
		this->mouseOnTxtData = textData;
		this->buttonText.setFont(font);
		this->buttonText.setString(string);
		TextDataUpdate();
	}


	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& data, float scale, sf::Font& font,
		const textData& textData, buttonFunc func) : BaseButton(pos, data, data, scale, func) {
		this->mouseOutTxtData = textData;
		this->mouseOnTxtData = textData;
		this->buttonText.setFont(font);
		TextDataUpdate();
	}


	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, sf::Font& font,
		const textData& mouseOutText, const textData& mouseOnText, std::wstring string,
		sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func,
			mouseEnteredSound, clickSound) {
		this->mouseOutTxtData = mouseOutText;
		this->mouseOnTxtData = mouseOnText;
		this->buttonText.setFont(font);
		this->buttonText.setString(string);
		TextDataUpdate();
	}





	////////////////////////////////////////////////////////
	//ImageButton



	void ImageButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(buttonBackground);
		target.draw(buttonImage);
	}




	ImageButton::ImageButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale,
		sf::Texture& image, float iconScale, buttonFunc func) : BaseButton(pos, mouseOut,
			mouseOn, buttonScale, func) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(iconScale, iconScale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
	}

	ImageButton::ImageButton(sf::Vector2f pos, const rectangleShapeData& data, float buttonScale, sf::Texture& image, float iconScale, buttonFunc func) : BaseButton(pos, data, data, buttonScale, func) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(iconScale, iconScale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
	}

	ImageButton::ImageButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale, sf::Texture& image, float iconScale, sf::SoundBuffer& mouseEnteredSound,
		sf::SoundBuffer& clickSound, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, buttonScale, func, mouseEnteredSound, clickSound) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(iconScale, iconScale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
	}

	///////////////////////////////////////////////////////
	//CheckBox



	void CheckBox::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->CheckClick(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			if (this->isChecked)
				this->isChecked = false;
			else
				this->isChecked = true;
			if (func != nullptr)
				func();
		}
	}

	void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(this->buttonBackground, states);

		if (isChecked)
			target.draw(this->buttonImage, states);
	}

	CheckBox::CheckBox(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale,
		sf::Texture& checkIcon, float iconScale, buttonFunc whenStateChanges) : ImageButton(pos, mouseOut, mouseOn,
			buttonScale, checkIcon, iconScale, whenStateChanges), isChecked(false) {

	}


	CheckBox::CheckBox(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale,
		sf::Texture& checkIcon, float iconScale, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound,
		buttonFunc whenStateChanges) : ImageButton(pos, mouseOut, mouseOn,
			buttonScale, checkIcon, iconScale, mouseEnteredSound, clickSound, whenStateChanges), isChecked(false) {

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