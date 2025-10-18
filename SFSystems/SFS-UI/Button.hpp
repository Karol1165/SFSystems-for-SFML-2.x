#pragma once
#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "framework.h"

#include "UIViews.hpp"

namespace SFS {
	/////////////////////////////////////////////////////////////////
	//BaseButton

	using buttonFunc = void(*) ();

	/// <summary>
	/// Base class for all buttons
	/// </summary>

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
		BaseButton() = default;
		~BaseButton() = default;

		BaseButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, buttonFunc func);
		BaseButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, buttonFunc func,
			const soundData& mouseEnteredSound,
			const soundData& clickSound);



		[[nodiscard]]
		sf::Vector2f getPos() const {
			return buttonBackground.getPosition();
		}

		[[nodiscard]]
		sf::FloatRect getGlobalBounds() const {
			return buttonBackground.getGlobalBounds();
		}


		virtual void setPos(sf::Vector2f newPos) {
			this->buttonBackground.setPosition(newPos);
		}
		virtual void setMouseOutButtonData(rectangleShapeData& newData) {
			this->buttonBgrData.mouseOut = newData;
		}
		virtual void setMouseOnButtonData(rectangleShapeData& newData) {
			this->buttonBgrData.mouseOn = newData;
		}
		virtual void setButtonData(rectangleShapeData& newData) {
			this->buttonBgrData.mouseOn = newData;
			this->buttonBgrData.mouseOut = newData;
		}
		virtual void setMouseEnteredSoundData(soundData& newData) {
			setSoundData(newData, this->mouseEnteredSound);
		}
		virtual void setClickSoundData(soundData& newData) {
			setSoundData(newData, this->clickSound);
		}

		virtual void setFunction(buttonFunc newFunc) {
			if (newFunc)
				this->func = newFunc;
		}

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));
	};

	///////////////////////////////////////////
	// TextButton


	/// <summary>
	/// Class for a buttons that have text on it
	/// </summary>

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
		void TextInit(const textData& mouseOutText, const textData& mouseOnText, std::wstring& string);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual bool CheckClick(sf::Vector2f mousePos, bool isClicked);
	public:
		//Constructors
		TextButton() = default;
		~TextButton() = default;

		TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn,
			const textData& mouseOutText, const textData& mouseOnText,
			std::wstring string, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn,
			const textData& mouseOutText, const textData& mouseOnText, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, const rectangleShapeData& data,
			const textData& textData, std::wstring string, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, const rectangleShapeData& data,
			const textData& textData, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn,
			const textData& mouseOutText, const textData& mouseOnText, std::wstring string,
			const soundData& mouseEnteredSound, const soundData& clickSound, buttonFunc func = nullptr);

		//Get

		[[nodiscard]]
		std::wstring getString() const {
			return buttonText.getString();
		}

		//Set

		void setPos(sf::Vector2f newPos)  override {
			buttonBackground.setPosition(newPos);
			TextPosUpdate();
		}
		void setMouseOutButtonData(rectangleShapeData& newData) override {
			BaseButton::setMouseOutButtonData(newData);
			TextPosUpdate();
		}
		void setMouseOnButtonData(rectangleShapeData& newData) override {
			BaseButton::setMouseOnButtonData(newData);
			TextPosUpdate();
		}
		void setButtonData(rectangleShapeData& newData) override {
			BaseButton::setButtonData(newData);
			TextPosUpdate();
		}
		void setMouseOnTextData(textData& newData) {
			this->mouseOnTxtData = newData;
		}
		void setMouseOutTextData(textData& newData) {
			this->mouseOutTxtData = newData;
		}
		void setButtonTextData(textData& newData) {
			this->mouseOnTxtData = newData;
			this->mouseOutTxtData = newData;
		}
		void setString(std::wstring newString) {
			buttonText.setString(newString);
			TextPosUpdate();
		}
	};

	///////////////////////////////////////////////////
	//ImageButton

	/// <summary>
	/// Class for buttons that have icon/image on it
	/// </summary>

	class SFS_UI_API ImageButton : public BaseButton {
	protected:
		sf::Sprite buttonImage;

		void ImagePosUpdate() { buttonImage.setPosition(centerSprite(buttonImage, buttonBackground)); }
		void ImageInit(sf::Texture& image, float iconScale);

		/// <summary>
		/// Draws button
		/// </summary>
		/// <param name="target"></param>
		/// <param name="states"></param>
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

	public:

		ImageButton() = default;

		~ImageButton() = default;

		ImageButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, sf::Texture& image,
			float iconScale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, const rectangleShapeData& backgroundData, sf::Texture& image, float iconScale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn,
			sf::Texture& image, float iconScale, const soundData& mouseEnteredSound, const soundData& clickSound, buttonFunc func = nullptr);
	};


	//////////////////////////////////////////////////////
	//CheckBox

	class SFS_UI_API CheckBox : public ImageButton {
	protected:

		bool isChecked = false;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		CheckBox() = default;
		~CheckBox() = default;

		CheckBox(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn,
			sf::Texture& checkIcon, float iconScale, bool isChecked = false, buttonFunc whenStateChanges = nullptr);

		CheckBox(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn,
			sf::Texture& checkIcon, float iconScale, const soundData& mouseEnteredSound, const soundData& clickSound,
			bool isChecked = false, buttonFunc whenStateChanges = nullptr);

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));

		[[nodiscard]]
		bool getState() const {
			return this->isChecked;
		}

		void setState(bool isChecked) {
			this->isChecked = isChecked;
		}

	};

	///////////////////////////////////////////////////
	//RadioButton
	//TODO:

	/*

	class SFS_UI_API RadioButtonGroup;

	class RadioButton;

	class RadioButtonGroup : public UI {
	public:
		std::vector<ptr<RadioButton>> buttons;
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