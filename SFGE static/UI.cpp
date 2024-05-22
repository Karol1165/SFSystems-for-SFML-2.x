#include "pch.h"
#include "UI.hpp"

namespace SFGF {
	
	//BaseButton
	

	/// <summary>
	/// Checking click, setting background and playing sounds of click
	/// </summary>
	/// <param name="mousePos"></param>
	/// <param name="isClicked"></param>
	/// <returns></returns>

	bool BaseButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
		if (mousePos.x > buttonBackground.getPosition().x &&
			mousePos.x < buttonBackground.getPosition().x + buttonBackground.getGlobalBounds().width &&
			mousePos.y > buttonBackground.getPosition().y &&
			mousePos.y < buttonBackground.getPosition().y + buttonBackground.getGlobalBounds().height) {
			buttonBackground.setTexture(buttonBgrData.mouseOn);
			if (isClicked) {
				clickSound.play();
				return true;
			}
			else
				return false;
			if (!isMouseOn) {
				isMouseOn = true;
				mouseEnteredSound.play();
			}
		}
		else {
			isMouseOn = false;
			buttonBackground.setTexture(buttonBgrData.mouseOut); 
			return false;
		}
	}

	//TextButton

	/// <summary>
	/// Returns position of text on the center of sprite
	/// </summary>
	/// <param name="Text"></param>
	/// <param name="button"></param>
	/// <returns></returns>

	sf::Vector2f TextButton::centerText(const sf::Text& Text, const sf::Sprite& button) {
		sf::FloatRect textRect = Text.getLocalBounds();
		return sf::Vector2f(button.getPosition().x + (button.getGlobalBounds().width - textRect.width) / 2.0f - textRect.left,
			button.getPosition().y + (button.getGlobalBounds().height - textRect.height) / 2.0f - textRect.top);
	}

	/// <summary>
	/// Draw button
	/// </summary>
	/// <param name="target"></param>
	/// 
	/*
	virtual void TextButton::draw(sf::RenderTarget& target) const override{
		target.draw(buttonBackground);
		target.draw(buttonText);
	}
	*/

	bool TextButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
		if (mousePos.x > buttonBackground.getPosition().x &&
			mousePos.x < buttonBackground.getPosition().x + buttonBackground.getGlobalBounds().width &&
			mousePos.y > buttonBackground.getPosition().y &&
			mousePos.y < buttonBackground.getPosition().y + buttonBackground.getGlobalBounds().height) {
			buttonBackground.setTexture(buttonBgrData.mouseOn);
			buttonText.setFillColor(buttonTxtData.mouseOn);
			if (isClicked) {
				clickSound.play();
				return true;
			}
			else
				return false;
			if (!isMouseOn) {
				isMouseOn = true;
				mouseEnteredSound.play();
			}
		}
		else {
			isMouseOn = false;
			buttonBackground.setTexture(buttonBgrData.mouseOut);
			buttonText.setFillColor(buttonTxtData.mouseOut);
			return false;
		}
	}

	template <typename F>
	TextButton::TextButton(sf::Vector2f pos,sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
		std::wstring string, F func) {
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setPosition(pos);
		this->buttonBackground.setScale(scale);
		this->buttonTxtData.mouseOut = mouseOutColor;
		this->buttonTxtData.mouseOn = mouseOnColor;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
		this->buttonText.setString(string);
		TextPosUpdate();
		this->func = func;
	}
	template <typename F>
	TextButton::TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
		 F func) {
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setPosition(pos);
		this->buttonBackground.setScale(scale);
		this->buttonTxtData.mouseOut = mouseOutColor;
		this->buttonTxtData.mouseOn = mouseOnColor;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
		this->func = func;
	}
	template <typename F>
	TextButton::TextButton(sf::Vector2f pos, sf::Texture& sprite, int scale, sf::Font& font, int fontSize, sf::Color color,std::wstring string, F func) {
		this->buttonBgrData.mouseOut = sprite;
		this->buttonBgrData.mouseOn = sprite;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setPosition(pos);
		this->buttonBackground.setScale(scale);
		this->buttonTxtData.mouseOut = color;
		this->buttonTxtData.mouseOn = color;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
		this->buttonText.setString(string);
		TextPosUpdate();
		this->func = func;
	}
	template <typename F>
	TextButton::TextButton(sf::Vector2f pos, sf::Texture& texture, int scale, sf::Font& font, int fontSize, sf::Color color, F func) {
		this->buttonBgrData.mouseOut = texture;
		this->buttonBgrData.mouseOn = texture;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setPosition(pos);
		this->buttonBackground.setScale(scale);
		this->buttonTxtData.mouseOut = color;
		this->buttonTxtData.mouseOn = color;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
		this->func = func;
	}
	template<typename F>
	TextButton::TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
		std::wstring string, sf::Sound& mouseEnteredSound, sf::Sound& clickSound, F func){
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setPosition(pos);
		this->buttonBackground.setScale(scale);
		this->buttonTxtData.mouseOut = mouseOutColor;
		this->buttonTxtData.mouseOn = mouseOnColor;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
		this->buttonText.setString(string);
		TextPosUpdate();
		this->mouseEnteredSound = mouseEnteredSound;
		this->clickSound = clickSound;
		this->func = func;
	}

	

	/// <summary>
	/// Update method of button. Checks click and doing other operations
	/// </summary>
	/// <param name="mousePos"></param>
	/// <param name="isLeftMousePressed"></param>
	/// <param name="isRightMousePressed"></param>
	void TextButton::CheckStatus(sf::Vector2f& mousePos, bool isLeftMousePressed, bool isRightMousePressed) {
		if (CheckClick(mousePos, isLeftMousePressed)) {
			//Do button function
			this->func();
		}
	}

	//ImageButton

	/// <summary>
	/// Returns position of sprite, where this sprite is on center of other sprite
	/// </summary>
	/// <param name="spriteToCenter"></param>
	/// <param name="referenceSprite"></param>
	/// <returns>Centered position of sprite</returns>
	sf::Vector2f ImageButton::centerSprite(sf::Sprite& spriteToCenter, sf::Sprite& referenceSprite) {
		float xPos = referenceSprite.getPosition().x + (referenceSprite.getLocalBounds().width - spriteToCenter.getLocalBounds().width) / 2;
		float yPos = referenceSprite.getPosition().y + (referenceSprite.getLocalBounds().height - spriteToCenter.getLocalBounds().height) / 2;

		return sf::Vector2f(xPos, yPos);
	}

	/// <summary>
	/// Draw button
	/// </summary>
	/// <param name="target"></param>
	void ImageButton::draw(sf::RenderTarget& target) const {
		target.draw(buttonBackground);
		target.draw(buttonImage);
	}

	void ImageButton::CheckStatus(sf::Vector2f mousePos, bool isLeftMouseClicked, bool isRightMouseClicked) {
		if (CheckClick(mousePos, isLeftMouseClicked)) {
			this->func();
		}
	}

	template<typename F>
	ImageButton::ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, sf::Texture& image, int scale, F func) {
		this->buttonBackground.setPosition(pos);
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setScale(scale);
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(scale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
		this->func = func;
	}
	template<typename F>
	ImageButton::ImageButton(sf::Vector2f pos, sf::Texture& texture, sf::Texture& image, int scale, F func) {
		this->buttonBackground.setPosition(pos);
		this->buttonBgrData.mouseOn = texture;
		this->buttonBgrData.mouseOut = texture;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setScale(scale);
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(scale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
		this->func = func;
	}
	template<typename F>
	ImageButton::ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, sf::Texture& image, int scale, sf::Sound& mouseEnteredSound,
		sf::Sound& clickSound, F func) {
		this->buttonBackground.setPosition(pos);
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setScale(scale);
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(scale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
		this->mouseEnteredSound = mouseEnteredSound;
		this->clickSound = clickSound;
		this->func = func;
	}
}