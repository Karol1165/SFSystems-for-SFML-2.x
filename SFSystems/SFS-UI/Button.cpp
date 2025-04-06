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
		if (this->CheckClick(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			//Do button function
			if (this->func != nullptr)
				this->func();
		}
	}



	void BaseButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(buttonBackground);
	}

	void BaseButton::BackgroundDataUpdate(bool isSpotted) {
		if (isSpotted) {
			setRectangleData(this->buttonBgrData.mouseOn, this->buttonBackground);
		}
		else {
			setRectangleData(this->buttonBgrData.mouseOut, this->buttonBackground);
		}
	}

	BaseButton::BaseButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, buttonFunc func) {
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setPosition(pos);
		setRectangleData(this->buttonBgrData.mouseOut, this->buttonBackground);
		this->func = func;
		this->isMouseOn = false;
	}


	BaseButton::BaseButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, buttonFunc func, const soundData& mouseEnteredSound,
		const soundData& clickSound) {
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setPosition(pos);
		setRectangleData(this->buttonBgrData.mouseOut, this->buttonBackground);
		this->func = func;
		setSoundData(mouseEnteredSound, this->mouseEnteredSound);
		setSoundData(clickSound, this->clickSound);
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
		if (isSpotted) {
			setTextData(this->mouseOnTxtData, this->buttonText);
		}
		else {
			setTextData(this->mouseOutTxtData, this->buttonText);
		}
		TextPosUpdate();
	}

	void TextButton::BackgroundDataUpdate(bool isSpotted) {
		BaseButton::BackgroundDataUpdate(isSpotted);
		TextPosUpdate();
		this->textView.setBounds(this->buttonBackground.getGlobalBounds());
	}


	void TextButton::TextInit(const textData& mouseOutText, const textData& mouseOnText, sf::Font& font) {
		this->mouseOutTxtData = mouseOutText;
		this->mouseOnTxtData = mouseOnText;
		this->buttonText.setFont(font);
		TextDataUpdate();
		this->textView.setBounds(this->buttonBackground.getGlobalBounds());
		this->textView.setObject(&this->buttonText);
	}

	void TextButton::TextInit(const textData& mouseOutText, const textData& mouseOnText, sf::Font& font, std::wstring& string) {
		this->mouseOutTxtData = mouseOutText;
		this->mouseOnTxtData = mouseOnText;
		this->buttonText.setFont(font);
		this->buttonText.setString(string);
		TextDataUpdate();
		this->textView.setBounds(this->buttonBackground.getGlobalBounds());
		this->textView.setObject(&this->buttonText);
	}


	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, sf::Font& font,
		const textData& mouseOutText, const textData& mouseOnText, std::wstring string,
		buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func) {
		this->TextInit(mouseOutText, mouseOnText, font, string);
	}



	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, sf::Font& font,
		const textData& mouseOutText, const textData& mouseOnText,
		buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func) {
		this->TextInit(mouseOutText, mouseOnText, font);
	}


	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& data, float scale, sf::Font& font,
		const textData& textData, std::wstring string, buttonFunc func)
		: BaseButton(pos, data, data, scale, func) {
		this->TextInit(textData, textData, font, string);
	}


	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& data, float scale, sf::Font& font,
		const textData& textData, buttonFunc func) : BaseButton(pos, data, data, scale, func) {
		this->TextInit(textData, textData, font);
	}


	TextButton::TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, sf::Font& font,
		const textData& mouseOutText, const textData& mouseOnText, std::wstring string,
		const soundData& mouseEnteredSound, const soundData& clickSound, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func,
			mouseEnteredSound, clickSound) {
		this->TextInit(mouseOutText, mouseOnText, font, string);
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


	ImageButton::ImageButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale,
		sf::Texture& image, float iconScale, buttonFunc func) : BaseButton(pos, mouseOut,
			mouseOn, buttonScale, func) {
		this->ImageInit(image, iconScale);
	}

	ImageButton::ImageButton(sf::Vector2f pos, const rectangleShapeData& data, float buttonScale, sf::Texture& image, float iconScale, buttonFunc func) : BaseButton(pos, data, data, buttonScale, func) {
		this->ImageInit(image, iconScale);
	}

	ImageButton::ImageButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale, sf::Texture& image, float iconScale, const soundData& mouseEnteredSound,
		const soundData& clickSound, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, buttonScale, func, mouseEnteredSound, clickSound) {
		this->ImageInit(image, iconScale);
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
		sf::Texture& checkIcon, float iconScale, const soundData& mouseEnteredSound, const soundData& clickSound,
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