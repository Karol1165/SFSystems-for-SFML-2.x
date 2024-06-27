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
		ClippedView<sf::Text> textView = ClippedView<sf::Text>(buttonBackground.getGlobalBounds());
		textView.setObject(buttonText);
		target.draw(textView);
	}
	

	bool TextButton::CheckClick(sf::Vector2f mousePos, bool isClicked) {
		bool isButtonClicked = false;
		if (buttonBackground.getGlobalBounds().contains(mousePos)) {
			this->buttonBackground.setTexture(this->buttonBgrData.mouseOn);
			TextDataUpdate(true);
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
			TextDataUpdate(false);
			this->buttonBackground.setTexture(this->buttonBgrData.mouseOut);
		}
		return isButtonClicked;
	}


	TextButton::TextButton(sf::Vector2f pos,sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
		std::wstring string, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func) {
		this->mouseOutTxtData = mouseOutText;
		this->mouseOnTxtData = mouseOnText;
		this->buttonText.setFont(font);
		this->buttonText.setString(string);
		TextDataUpdate();
	}



	TextButton::TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
		 buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func) {
		this->mouseOutTxtData = mouseOutText;
		this->mouseOnTxtData = mouseOnText;
		this->buttonText.setFont(font);
		TextDataUpdate();
	}


	TextButton::TextButton(sf::Vector2f pos, sf::Texture& texture, int scale, sf::Font& font, textData textData,std::wstring string, buttonFunc func)
		: BaseButton(pos, texture, texture, scale, func) {
		this->mouseOutTxtData = textData;
		this->mouseOnTxtData = textData;
		this->buttonText.setFont(font);
		this->buttonText.setString(string);
		TextDataUpdate();
	}


	TextButton::TextButton(sf::Vector2f pos, sf::Texture& texture, int scale, sf::Font& font, textData textData, buttonFunc func) : BaseButton(pos, texture, texture, scale, func) {
		this->mouseOutTxtData = textData;
		this->mouseOnTxtData = textData;
		this->buttonText.setFont(font);
		TextDataUpdate();
	}


	TextButton::TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
		std::wstring string, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, scale, func,
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




	ImageButton::ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int buttonScale, sf::Texture& image, int iconScale, buttonFunc func) : BaseButton(pos, mouseOut,
		mouseOn, buttonScale, func) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(iconScale, iconScale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
	}

	ImageButton::ImageButton(sf::Vector2f pos, sf::Texture& texture, int buttonScale, sf::Texture& image, int iconScale, buttonFunc func) : BaseButton(pos, texture,
		texture, buttonScale, func) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(iconScale, iconScale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
	}

	ImageButton::ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int buttonScale, sf::Texture& image, int iconScale, sf::SoundBuffer& mouseEnteredSound,
		sf::SoundBuffer& clickSound, buttonFunc func) : BaseButton(pos, mouseOut, mouseOn, buttonScale, func, mouseEnteredSound, clickSound) {
		this->buttonImage.setTexture(image);
		this->buttonImage.setScale(iconScale, iconScale);
		this->buttonImage.setPosition(centerSprite(buttonImage, buttonBackground));
	}

	///////////////////////////////////////////////////////
	//CheckBox

	void CheckBox::CheckStatus(const sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->CheckClick(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			this->state = checked;
			if (func != nullptr)
				func();
		}
	}

	void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(this->buttonBackground, states);

		if(state == checked)
			target.draw(this->buttonImage, states);
	}

	CheckBox::CheckBox(sf::Vector2f pos, sf::Texture& mouseOutTex, sf::Texture& mouseOnTex, int buttonScale, sf::Texture& checkIcon, int iconScale, buttonFunc whenStateChanges) : ImageButton(pos, mouseOutTex, mouseOnTex,
		buttonScale, checkIcon, iconScale, whenStateChanges), state(unchecked) {

	}


	CheckBox::CheckBox(sf::Vector2f pos, sf::Texture& mouseOutTex, sf::Texture& mouseOnTex, int buttonScale, sf::Texture& checkIcon, int iconScale, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound,
		buttonFunc whenStateChanges) : ImageButton(pos, mouseOutTex, mouseOnTex,
			buttonScale, checkIcon, iconScale, mouseEnteredSound, clickSound, whenStateChanges), state(unchecked) {

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

	void Switch::textSwitchButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		TextButton::draw(target, states);
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
		std::wstring string, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner) : TextButton(pos, mouseOut, mouseOn, scale, font, mouseOutText, mouseOnText,
		string, mouseEnteredSound, clickSound) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, sf::Texture& texture, int scale, sf::Font& font, textData textData, std::wstring string, mode buttonMode, Switch* owner) :
		TextButton(pos, texture, scale, font, textData, string) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::textSwitchButton::textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
		std::wstring string, mode buttonMode, Switch* owner) : TextButton(pos, mouseOut, mouseOn, scale, font, mouseOutText, mouseOnText, string) {
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

	void Switch::imageSwitchButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		ImageButton::draw(target, states);
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int buttonScale, sf::Texture& image, int iconScale, mode buttonMode, Switch* owner)
		: ImageButton (pos, mouseOut, mouseOn, buttonScale, image, iconScale) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, sf::Texture& texture,int buttonScale, sf::Texture& image, int iconScale, mode buttonMode, Switch* owner)
		: ImageButton(pos, texture,buttonScale, image, iconScale) {
		this->buttonMode = buttonMode;
		this->owner = owner;
	}

	Switch::imageSwitchButton::imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int buttonScale,sf::Texture& image, int iconScale, sf::SoundBuffer& mouseEnteredSound,
		sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner) : ImageButton(pos, mouseOut,
			mouseOn, buttonScale, image, iconScale, mouseEnteredSound, clickSound) {
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

		ClippedView<sf::Text> textView = ClippedView<sf::Text>(this->background.getGlobalBounds());
		textView.setObject(text);
		target.draw(textView, states);

		target.draw(*this->leftButton, states);
		target.draw(*this->rightButton, states);


	}

	Switch::Switch(sf::Vector2f pos,rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonMouseOutTex,
		sf::Texture& buttonMouseOnTex, int buttonScale, sf::Font& buttonFont, textData buttonMouseOutText, textData buttonMouseOnText, sf::SoundBuffer& buttonSpottedSound,
		sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText, std::wstring rightButtonText, SwitchStates states) {

		this->leftButton = std::shared_ptr<baseSwitchButton>( new textSwitchButton(pos, buttonMouseOutTex, buttonMouseOnTex, buttonScale, buttonFont, buttonMouseOutText, buttonMouseOnText, leftButtonText, buttonSpottedSound,
			buttonClickSound, baseSwitchButton::mode::last, this) );

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		this->background.setFillColor(backgroundData.fillColor);
		this->background.setSize(backgroundData.size);
		this->background.setOutlineColor(backgroundData.outlineColor);
		this->background.setOutlineThickness(backgroundData.outlineThickness);
		


		this->rightButton = std::shared_ptr<baseSwitchButton>(new textSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonMouseOutTex,
			buttonMouseOnTex, buttonScale, buttonFont, buttonMouseOutText, buttonMouseOnText, rightButtonText, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::next, this));



		this->text.setFont(textFont);
		this->text.setFillColor(optionTextData.fillColor);
		this->text.setCharacterSize(optionTextData.characterSize);
		this->text.setOutlineColor(optionTextData.outlineColor);
		this->text.setOutlineThickness(optionTextData.outlineThickness);

		this->states = states;

		this->text.setString(this->states.getActualOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonTex, int buttonScale,
		sf::Font& buttonFont,textData buttonTextData, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText,
		std::wstring rightButtonText, SwitchStates states) {
		this->leftButton = std::shared_ptr<baseSwitchButton>(new textSwitchButton(pos, buttonTex,buttonTex , buttonScale, buttonFont, buttonTextData, buttonTextData , leftButtonText, buttonSpottedSound, buttonClickSound, baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		this->background.setFillColor(backgroundData.fillColor);
		this->background.setSize(backgroundData.size);
		this->background.setOutlineColor(backgroundData.outlineColor);
		this->background.setOutlineThickness(backgroundData.outlineThickness);

		this->rightButton = std::shared_ptr<baseSwitchButton>(new textSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonTex,
			buttonTex, buttonScale, buttonFont, buttonTextData, buttonTextData, rightButtonText, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::next, this));

		this->text.setFont(textFont);
		this->text.setFillColor(optionTextData.fillColor);
		this->text.setCharacterSize(optionTextData.characterSize);
		this->text.setOutlineColor(optionTextData.outlineColor);
		this->text.setOutlineThickness(optionTextData.outlineThickness);

		this->states = states;

		this->text.setString(this->states.getActualOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonMouseOutTex,
		sf::Texture& buttonMouseOnTex, int buttonScale, sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, int buttonIconScale, sf::SoundBuffer& buttonSpottedSound,
		sf::SoundBuffer& buttonClickSound, SwitchStates states){

		this->leftButton = std::shared_ptr<baseSwitchButton>( new imageSwitchButton(pos, buttonMouseOutTex, buttonMouseOnTex,buttonScale, leftButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		this->background.setFillColor(backgroundData.fillColor);
		this->background.setSize(backgroundData.size);
		this->background.setOutlineColor(backgroundData.outlineColor);
		this->background.setOutlineThickness(backgroundData.outlineThickness);

		this->rightButton = std::shared_ptr<baseSwitchButton>(new imageSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonMouseOutTex, buttonMouseOnTex,
			buttonScale, rightButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound, baseSwitchButton::mode::next, this));

		this->text.setFont(textFont);
		this->text.setFillColor(optionTextData.fillColor);
		this->text.setOutlineColor(optionTextData.outlineColor);
		this->text.setOutlineThickness(optionTextData.outlineThickness);
		this->text.setCharacterSize(optionTextData.characterSize);

		this->states = states;

		this->text.setString(this->states.getActualOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}

	Switch::Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonTex, int buttonScale,
		sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, int buttonIconScale, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, SwitchStates states) {

		this->leftButton = std::shared_ptr<baseSwitchButton>(new imageSwitchButton(pos, buttonTex, buttonTex,buttonScale, leftButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound,
			baseSwitchButton::mode::last, this));

		this->background.setPosition(sf::Vector2f(pos.x + leftButton->getGlobalBounds().width + backgroundData.outlineThickness * 2, pos.y + leftButton->getGlobalBounds().height / 2 - backgroundData.size.y / 2));
		this->background.setFillColor(backgroundData.fillColor);
		this->background.setSize(backgroundData.size);
		this->background.setOutlineColor(backgroundData.outlineColor);
		this->background.setOutlineThickness(backgroundData.outlineThickness);

		this->rightButton = std::shared_ptr<baseSwitchButton>(new imageSwitchButton(sf::Vector2f(this->background.getPosition().x + this->background.getGlobalBounds().width, pos.y), buttonTex, buttonTex, buttonScale,
			rightButtonImage, buttonIconScale, buttonSpottedSound, buttonClickSound, baseSwitchButton::mode::next, this));

		this->text.setFont(textFont);
		this->text.setFillColor(optionTextData.fillColor);
		this->text.setOutlineColor(optionTextData.outlineColor);
		this->text.setOutlineThickness(optionTextData.outlineThickness);
		this->text.setCharacterSize(optionTextData.characterSize);

		this->states = states;

		this->text.setString(this->states.getActualOption().getName());
		this->text.setPosition(centerText(this->text, this->background));
	}
	
	void Switch::CheckStatus(const sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		this->leftButton->CheckStatus(e, deltaTime, mousePos);
		this->rightButton->CheckStatus(e, deltaTime, mousePos);
	}

	///////////////////////////////////////////////////////////////////
	//Views
	///////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////
	//ClippedView

	template<DrawableType T>
	void ClippedView<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		sf::View view(bounds);
		renderTexture.setView(view);

		// Clear the render texture with transparency
		renderTexture.clear(sf::Color::Transparent);

		// Draw the stored drawable onto the render texture
		renderTexture.draw(*object, states);

		// Display the render texture to update its contents
		renderTexture.display();

		// Create a sprite with the texture of the render texture
		sf::Sprite sprite(renderTexture.getTexture());
		sprite.setPosition(bounds.left, bounds.top);

		// Draw the sprite on the target render
		target.draw(sprite, states);
	}



	///////////////////////////////////////////////////////////////////////////
	//Other
	//////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////
	//TextBox


	TextBox::TextBox(sf::Vector2f pos, rectangleShapeData boxData, textData textData, sf::Font& font) : isActive(false) {
		this->background.setPosition(pos);
		this->background.setSize(boxData.size);
		this->background.setFillColor(boxData.fillColor);
		this->background.setOutlineColor(boxData.outlineColor);
		this->background.setOutlineThickness(boxData.outlineThickness);

		this->text.setFont(font);
		this->text.setCharacterSize(textData.characterSize);
		this->text.setFillColor(textData.fillColor);
		this->text.setOutlineColor(textData.outlineColor);
		this->text.setOutlineThickness(textData.outlineThickness);
	}

	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(background, states);
		ClippedView<sf::Text> textView = ClippedView<sf::Text>(background.getGlobalBounds());
		textView.setObject(this->text);
		target.draw(textView, states);
	}

	void TextBox::CheckStatus(const sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (e.type == sf::Event::MouseButtonPressed) {
			if (e.mouseButton.button == sf::Mouse::Left) {
				if (background.getGlobalBounds().contains(mousePos)) {
					isActive = true;
				}
				else {
					isActive = false;
				}
			}
		}
		if (isActive && e.type == sf::Event::TextEntered) {
			if (e.text.unicode == 8) { // Handle backspace
				std::wstring str = static_cast<std::wstring>( text.getString() );
				if (!str.empty()) {
					str.pop_back();
					text.setString(sf::String(str));
				}
			}
			else if (e.text.unicode >= 32 && e.text.unicode != 127) {
				text.setString(text.getString() + static_cast<wchar_t>(e.text.unicode));
			}

			this->text.setPosition(centerText(this->text, this->background));
			
			
		}
	}

}

