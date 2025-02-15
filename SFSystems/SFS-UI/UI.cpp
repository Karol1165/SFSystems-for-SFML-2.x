#include "pch.h"
#include "UI.hpp"

namespace SFS {

	/////////////////////////////////////////////////////////
	//BaseButton
	


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
	

	void BaseButton::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (this->CheckClick(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			//Do button function
			if(this->func != nullptr)
				this->func();
		}
	}



	void BaseButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(buttonBackground);
	}


	BaseButton::BaseButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, buttonFunc func) {
		this->buttonBgrData.mouseOut = mouseOut;
		this->buttonBgrData.mouseOn = mouseOn;
		this->buttonBackground.setTexture(buttonBgrData.mouseOut);
		this->buttonBackground.setPosition(pos);
		this->buttonBackground.setScale(scale, scale);
		this->func = func;
		isMouseOn = false;
	}


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



	
	void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(buttonBackground);
		ClippedView<sf::Text> textView = ClippedView<sf::Text>(buttonBackground.getGlobalBounds());
		textView.setObject(&buttonText);
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

		if(isChecked)
			target.draw(this->buttonImage, states);
	}

	CheckBox::CheckBox(sf::Vector2f pos, sf::Texture& mouseOutTex, sf::Texture& mouseOnTex, int buttonScale, sf::Texture& checkIcon, int iconScale, buttonFunc whenStateChanges) : ImageButton(pos, mouseOutTex, mouseOnTex,
		buttonScale, checkIcon, iconScale, whenStateChanges), isChecked(false) {

	}


	CheckBox::CheckBox(sf::Vector2f pos, sf::Texture& mouseOutTex, sf::Texture& mouseOnTex, int buttonScale, sf::Texture& checkIcon, int iconScale, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound,
		buttonFunc whenStateChanges) : ImageButton(pos, mouseOutTex, mouseOnTex,
			buttonScale, checkIcon, iconScale, mouseEnteredSound, clickSound, whenStateChanges), isChecked(false) {

	}

	//////////////////////////////////////////////////////////
	//RadioButton

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
		textView.setObject(&text);
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
	
	void Switch::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		this->leftButton->CheckStatus(e, deltaTime, mousePos);
		this->rightButton->CheckStatus(e, deltaTime, mousePos);
	}




	////////////////////////////////////////////
	//TextBox


	TextBox::TextBox(sf::Vector2f pos, rectangleShapeData boxData, rectangleShapeData activeBoxData, textData textData, sf::Font& font) : isChecked(false) {
		this->notActiveTextBoxData = boxData;
		this->activeTextBoxData = activeBoxData;

		this->background.setPosition(pos);
		setRectangleData(notActiveTextBoxData, this->background);

		this->text.setFont(font);
		setTextData(textData, this->text);
	}

	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(background, states);
		ClippedView<sf::Text> textView = ClippedView<sf::Text>(background.getGlobalBounds());
		textView.setObject(&text);
		target.draw(textView, states);
	}

	void TextBox::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (e.type == sf::Event::MouseButtonPressed) {
			if (e.mouseButton.button == sf::Mouse::Left) {
				if (background.getGlobalBounds().contains(mousePos)) {
					setRectangleData(activeTextBoxData, this->background);
					this->text.setPosition(centerText(this->text, this->background));
					isChecked = true;
				}
				else {
					isChecked = false;
					setRectangleData(notActiveTextBoxData, this->background);
					this->text.setPosition(centerText(this->text, this->background));
				}
			}
		}
		if (isChecked && e.type == sf::Event::TextEntered) {
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

	////////////////////////////////////////
	//toolTip

	toolTip::toolTip(rectangleShapeData backgroundData, textData tipTextData, sf::Vector2f pos, std::wstring text, sf::Font& textFont, sf::FloatRect fieldWhenVisible,
		sf::Time timeToActivate) {
		sf::Text tipText;
		setRectangleData(backgroundData, this->background);
		setTextData(tipTextData, tipText);
		this->background.setPosition(pos);
		this->fieldWhenActive = fieldWhenVisible;
		tipText.setFont(textFont);
		tipText.setString(text);
		tipText.setPosition(centerText(tipText, background));

		this->Text.setObject(new sf::Text(tipText));
		this->Text.setBounds(background.getGlobalBounds());

		if (timeToActivate != sf::Time::Zero) {
			this->requiredMouseOverTime = sf::Time::Zero;
			this->mouseOverTime = sf::Time::Zero;
		}

		this->isVisible = false;
	}

	void toolTip::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if(!this->requiredMouseOverTime.has_value())
			this->isVisible = this->fieldWhenActive.contains(mousePos);
		else {
			if (this->fieldWhenActive.contains(mousePos))
				*this->mouseOverTime += deltaTime;
			else
				this->mouseOverTime = sf::Time::Zero;
			if (this->mouseOverTime >= this->requiredMouseOverTime)
				this->isVisible = true;
			else
				this->isVisible = false;
		}
	}

	void toolTip::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (isVisible) {
			target.draw(this->background, states);
			target.draw(this->Text, states);
		}
	}

}

