#pragma once
#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "framework.h"

#include "UIViews.hpp"

namespace SFS {


	using buttonFunc = void(*) ();


	// Base class for all buttons

	class SFS_UI_API BaseButton : public UI {
	protected:
		struct ButtonBgrStatesData {
			rectangleShapeData mouseOn;
			rectangleShapeData mouseOut;
		};

		sf::RectangleShape buttonBackground;
		ButtonBgrStatesData buttonBgrData;

		sf::Sound mouseEnteredSound;
		sf::Sound clickSound;

		bool isMouseOn = false;

		buttonFunc func = nullptr;

		virtual void BackgroundDataUpdate(bool isSpotted = false);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual bool CheckClick(sf::Vector2f, bool);
	public:
		struct StyleData {
			rectangleShapeData mouseOnBgrData;
			rectangleShapeData mouseOutBgrData;
			soundData mouseEnteredSoundData;
			soundData clickSoundData;
		};

		BaseButton() = default;
		~BaseButton() = default;

		BaseButton(const sf::Vector2f& pos, const StyleData& style, buttonFunc func);

		[[nodiscard]]
		sf::Vector2f getPos() const {
			return buttonBackground.getPosition();
		}

		[[nodiscard]]
		sf::FloatRect getGlobalBounds() const {
			return buttonBackground.getGlobalBounds();
		}


		virtual void setPos(const sf::Vector2f& newPos) {
			this->buttonBackground.setPosition(newPos);
		}
		void setStyle(const StyleData& newStyle) {
			this->buttonBgrData.mouseOn = newStyle.mouseOnBgrData;
			this->buttonBgrData.mouseOut = newStyle.mouseOutBgrData;
			setSoundData(newStyle.mouseEnteredSoundData, this->mouseEnteredSound);
			setSoundData(newStyle.clickSoundData, this->clickSound);
		}

		virtual void setFunction(buttonFunc newFunc) {
			if (newFunc)
				this->func = newFunc;
		}

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));
	};



	// Class for a buttons that have text on it


	class SFS_UI_API TextButton : public BaseButton {
	protected:

		sf::Text buttonText;
		ClippedView textView;
		textData mouseOutTxtData;
		textData mouseOnTxtData;

		void TextPosUpdate() { buttonText.setPosition(centerText(buttonText, buttonBackground)); }

		void TextDataUpdate(bool isSpotted = false);

		void BackgroundDataUpdate(bool isSpotted = false) override;

		void TextInit(const textData& mouseOutText, const textData& mouseOnText);
		void TextInit(const textData& mouseOutText, const textData& mouseOnText, const sf::String& string);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual bool CheckClick(sf::Vector2f mousePos, bool isClicked);
	public:
		struct StyleData : public BaseButton::StyleData {
			textData mouseOnTextData;
			textData mouseOutTextData;
		};

		//Constructors
		TextButton() = default;
		~TextButton() = default;

		TextButton(const sf::Vector2f& pos, const StyleData& style,
			const sf::String& string, buttonFunc func = nullptr);

		TextButton(const sf::Vector2f& pos, const StyleData& style, buttonFunc func = nullptr);

		//Get

		[[nodiscard]]
		sf::String getString() const {
			return buttonText.getString();
		}

		//Set

		void setPos(const sf::Vector2f& newPos)  override {
			buttonBackground.setPosition(newPos);
			TextPosUpdate();
		}

		void setStyle(const StyleData& newStyle) {
			BaseButton::setStyle(newStyle);
			this->mouseOutTxtData = newStyle.mouseOutTextData;
			this->mouseOnTxtData = newStyle.mouseOnTextData;
			TextDataUpdate();
		}

		void setString(const sf::String& newString) {
			buttonText.setString(newString);
			TextPosUpdate();
		}
	};

	// Class for buttons that have icon/image on it

	class SFS_UI_API ImageButton : public BaseButton {
	protected:
		sf::Sprite buttonImage;

		void ImagePosUpdate() { buttonImage.setPosition(centerSprite(buttonImage, buttonBackground)); }
		void ImageInit(sf::Texture& image, float iconScale);

	
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

	public:
		struct StyleData : public BaseButton::StyleData {
			float imageScale = 1.0f;
		};

		ImageButton() = default;
		~ImageButton() = default;

		ImageButton(const sf::Vector2f& pos, const StyleData& style, sf::Texture& image,
		 buttonFunc func = nullptr);

		void setPos(const sf::Vector2f& newPos) override {
			this->buttonBackground.setPosition(newPos);
			ImagePosUpdate();
		}
	};


	//Class for chcecboxes

	class SFS_UI_API CheckBox : public ImageButton {
	protected:

		bool isChecked = false;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		struct StyleData : public ImageButton::StyleData {
			sf::Texture* checkIcon = nullptr;
		};

		CheckBox() = default;
		~CheckBox() = default;

		CheckBox(const sf::Vector2f& pos, const StyleData& style, bool isChecked = false, buttonFunc whenStateChanges = nullptr);

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));

		[[nodiscard]]
		bool getState() const {
			return this->isChecked;
		}

		void setState(bool isChecked) {
			this->isChecked = isChecked;
		}
	};


	//TODO:

	/*

	class SFS_UI_API RadioButtonGroup;

	class RadioButton;

	class RadioButtonGroup : public UI {
	public:
		std::vector<sptr<RadioButton>> buttons;
	};

	class SFS_UI_API RadioButton : public BaseButton {
	protected:
		RadioButtonGroup* group;
		bool isChecked;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void disableActive();

		virtual bool CheckClick(sf::Vector2f mousePos, bool isClicked);
	public:

		RadioButton() = default;
		~RadioButton() = default;

		RadioButton(const RadioButton& orginal) = default;

		RadioButton& operator=(const RadioButton&) = default;

		RadioButton(sf::Vector2f pos, sf::Texture& Tex, sf::Texture& activeTex, int butttonScale, buttonFunc whenStateChanges = nullptr);
		RadioButton(sf::Vector2f pos, sf::Texture& Tex, sf::Texture& activeTex, int butttonScale, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, buttonFunc whenStateChanges = nullptr);

		void setActive();

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));
	};
	*/
}

#endif