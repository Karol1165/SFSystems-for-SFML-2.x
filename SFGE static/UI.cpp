#include "pch.h"
#include "UI.hpp"

namespace SFGF {

	/////////////////////////////////////////////////////////
	//BaseButton
	

	/// <summary>
	/// Checking click, setting background and playing sounds of click
	/// </summary>
	/// <param name="mousePos"></param>
	/// <param name="isClicked"></param>
	/// <returns>if button is clicked: true, if not: false</returns>

	bool BaseButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
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
			buttonBackground.setTexture(buttonBgrData.mouseOut); 
		}
		return isButtonClicked;
	}
	

	/// <summary>
	/// An update func of button, checks click of button and doing actions
	/// </summary>
	/// <param name="e"></param>
	/// <param name="deltaTime"></param>
	/// <param name="mousePos"></param>
	void BaseButton::CheckStatus(const sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->CheckClick(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			//Do button function
			if(this->func != nullptr)
				this->func();
		}
	}


	/// <summary>
	/// Draws button
	/// </summary>
	/// <param name="target"></param>
	/// <param name="states"></param>
	void BaseButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(buttonBackground);
	}


	/// <summary>
	/// Simple constructor
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="mouseOut"></param>
	/// <param name="mouseOn"></param>
	/// <param name="scale"></param>
	/// <param name="func"></param>
	BaseButton::BaseButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, buttonFunc func) {
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setPosition(pos);
		this->buttonBackground.setScale(scale, scale);
		this->func = func;
		isMouseOn = false;
	}


	/// <summary>
	/// Fully constructor
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="mouseOut"></param>
	/// <param name="mouseOn"></param>
	/// <param name="scale"></param>
	/// <param name="func"></param>
	/// <param name="mouseEnteredSound"></param>
	/// <param name="clickSound"></param>
	BaseButton::BaseButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, buttonFunc func, sf::SoundBuffer& mouseEnteredSound,
		sf::SoundBuffer& clickSound) {
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setPosition(pos);
		this->buttonBackground.setScale(scale, scale);
		this->func = func;
		this->mouseEnteredSound.setBuffer(mouseEnteredSound);
		this->clickSound.setBuffer(clickSound);
		this->mouseEnteredSound.setVolume(100);
		this->clickSound.setVolume(100);
		this->isMouseOn = false;
	}

	/////////////////////////////////////////////////////
	//TextButton




	/// <summary>
	/// Draws button
	/// </summary>
	/// <param name="target"></param>
	/// 
	
	void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(buttonBackground);
		target.draw(buttonText);
	}
	

	bool TextButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
		bool isButtonClicked = false;
		if (buttonBackground.getGlobalBounds().contains(mousePos)) {
			buttonBackground.setTexture(buttonBgrData.mouseOn);
			buttonText.setFillColor(buttonTxtData.mouseOn);
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
			buttonBackground.setTexture(buttonBgrData.mouseOut);
			buttonText.setFillColor(buttonTxtData.mouseOut);
		}
		return isButtonClicked;
	}


	TextButton::TextButton(sf::Vector2f pos,sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
		std::wstring string, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func) {
		this->buttonTxtData.mouseOut = mouseOutColor;
		this->buttonTxtData.mouseOn = mouseOnColor;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
		this->buttonText.setString(string);
		TextPosUpdate();
	}



	TextButton::TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
		 buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func) {
		this->buttonTxtData.mouseOut = mouseOutColor;
		this->buttonTxtData.mouseOn = mouseOnColor;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
	}


	TextButton::TextButton(sf::Vector2f pos, sf::Texture& texture, int scale, sf::Font& font, int fontSize, sf::Color color,std::wstring string, buttonFunc func)
		: BaseButton(pos, texture, texture, scale, func) {
		this->buttonTxtData.mouseOut = color;
		this->buttonTxtData.mouseOn = color;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
		this->buttonText.setString(string);
		TextPosUpdate();
	}


	TextButton::TextButton(sf::Vector2f pos, sf::Texture& texture, int scale, sf::Font& font, int fontSize, sf::Color color, buttonFunc func) : BaseButton(pos, texture, texture, scale, func) {
		this->buttonTxtData.mouseOut = color;
		this->buttonTxtData.mouseOn = color;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
	}


	TextButton::TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
		std::wstring string, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func,
			mouseEnteredSound, clickSound) {
		this->buttonTxtData.mouseOut = mouseOutColor;
		this->buttonTxtData.mouseOn = mouseOnColor;
		this->buttonText.setFont(font);
		this->buttonText.setCharacterSize(fontSize);
		this->buttonText.setFillColor(buttonTxtData.mouseOut);
		this->buttonText.setString(string);
		TextPosUpdate();
	}





	////////////////////////////////////////////////////////
	//ImageButton



	void ImageButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(buttonBackground);
		target.draw(buttonImage);
	}




	ImageButton::ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, sf::Texture& image, int scale, buttonFunc func) : BaseButton(pos, mouseOut,
		mouseOn, scale, func) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(scale, scale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
	}

	ImageButton::ImageButton(sf::Vector2f pos, sf::Texture& texture, sf::Texture& image, int scale, buttonFunc func) : BaseButton(pos, texture,
		texture, scale, func) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(scale, scale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
	}

	ImageButton::ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, sf::Texture& image, int scale, sf::SoundBuffer& mouseEnteredSound,
		sf::SoundBuffer& clickSound, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func, mouseEnteredSound, clickSound) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(scale, scale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
	}

	//////////////////////////////////////////////////////////
	///Switch

	//Switch button
	
	void Switch::textSwitchButton::CheckStatus(const sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
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

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
		std::wstring string, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner) : TextButton(pos, mouseOut, mouseOn, scale, font, fontSize, mouseOutColor,
		mouseOnColor, string, mouseEnteredSound, clickSound) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, sf::Texture& texture, int scale, sf::Font& font, int fontSize, std::wstring string, sf::Color color, mode buttonMode, Switch* owner) :
		TextButton(pos, texture, scale, font, fontSize, color, string) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
		std::wstring string, mode buttonMode, Switch* owner) : TextButton(pos, mouseOut, mouseOn, scale, font, fontSize, mouseOutColor,
			mouseOnColor, string) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	sf::FloatRect Switch::textSwitchButton::getGlobalBounds() const {
		return this->buttonBackground.getGlobalBounds();
	}

	void Switch::imageSwitchButton::CheckStatus(const sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
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

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, sf::Texture& image, int scale, mode buttonMode, Switch* owner) : ImageButton (pos, mouseOut,
		mouseOn, image, scale) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, sf::Texture& texture, sf::Texture& image, int scale, mode buttonMode, Switch* owner) : ImageButton(pos, texture, image, scale) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, sf::Texture& image, int scale, sf::SoundBuffer& mouseEnteredSound,
		sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner) : ImageButton(pos, mouseOut,
			mouseOn, image, scale, mouseEnteredSound, clickSound) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}
	
	sf::FloatRect Switch::imageSwitchButton::getGlobalBounds() const {
		return this->buttonBackground.getGlobalBounds();
	}

	void Switch::UpdateText() {
		this->text.setString(this->states.getActualOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	void Switch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(this->background, states);
		target.draw(this->text, states);
		target.draw(*this->leftButton, states);
		target.draw(*this->rightButton, states);
	}

	Switch::Switch(sf::Vector2f pos, sf::Color backgroundColor, int backgroundRectLength, sf::Color textColor, sf::Font& textFont, int textFontSize, sf::Texture& buttonMouseOutTex,
		sf::Texture& buttonMouseOnTex, int buttonScale, sf::Font& buttonFont, int buttonFontSize, sf::Color buttonMouseOutColor, sf::Color buttonMouseOnColor, sf::SoundBuffer& buttonSpottedSound,
		sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText, std::wstring rightButtonText, SwitchStates states) {

		this->leftButton = std::shared_ptr<baseSwitchButton>( new textSwitchButton(pos, buttonMouseOutTex, buttonMouseOnTex, buttonScale, buttonFont, buttonFontSize, buttonMouseOutColor,
			buttonMouseOnColor, leftButtonText, buttonSpottedSound, buttonClickSound, baseSwitchButton::mode::last, this) );

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width, pos.y));
		this->background.setFillColor(backgroundColor);
		this->background.setSize(sf::Vector2f(backgroundRectLength, this->leftButton->getGlobalBounds().height));
		this->background.setOutlineThickness(0);
		
		this->rightButton = std::shared_ptr<baseSwitchButton>(new textSwitchButton(sf::Vector2f(this->background.getPosition().x + backgroundRectLength, pos.y), buttonMouseOutTex,
			buttonMouseOnTex, buttonScale, buttonFont, buttonFontSize, buttonMouseOutColor, buttonMouseOnColor, rightButtonText, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::next, this));

		this->text.setFont(textFont);
		this->text.setFillColor(textColor);
		this->text.setCharacterSize(textFontSize);

		this->states = states;

		this->text.setString(this->states.getActualOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	Switch::Switch(sf::Vector2f pos, sf::Color backgroundColor, int backgroundRectLength, sf::Color textColor, sf::Font& textFont, int textFontSize, sf::Texture& buttonTex, int buttonScale,
		sf::Font& buttonFont, int buttonFontSize, sf::Color buttonColor, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText,
		std::wstring rightButtonText, SwitchStates states) {

	}

	Switch::Switch(sf::Vector2f pos, sf::Color backgroundColor, int backgroundRectLength, sf::Color textColor, sf::Font& textFont, int textFontSize, sf::Texture& buttonMouseOutTex,
		sf::Texture& buttonMouseOnTex, int buttonScale, sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, int buttonImageScale, sf::SoundBuffer& buttonSpottedSound,
		sf::SoundBuffer& buttonClickSound, SwitchStates states){

	}

	Switch::Switch(sf::Vector2f pos, sf::Color backgroundColor, int backgroundRectLength, sf::Color textColor, sf::Font& textFont, int textFontSize, sf::Texture& buttonTex, int buttonScale,
		sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, int buttonImageScale, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, SwitchStates states) {

	}
	
	void Switch::CheckStatus(const sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		this->leftButton->CheckStatus(e, deltaTime, mousePos);
		this->rightButton->CheckStatus(e, deltaTime, mousePos);
	}

}