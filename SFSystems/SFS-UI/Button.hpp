#pragma once
#ifndef BUTTON_HPP_
#define BUTTON_HPP_
#include "Data.hpp"
#include "Base.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "framework.h"
#include "Math.hpp"
#include "UIViews.hpp"

namespace SFS {
	/////////////////////////////////////////////////////////////////
	//BaseButton

	/// <summary>
	/// Base class for all buttons
	/// </summary>

	class SFS_UI_API BaseButton : public UI {
	protected:
		typedef void(*buttonFunc) ();

		struct ButtonBgrStatesData {
			rectangleShapeData mouseOn;
			rectangleShapeData mouseOut;
		};

		sf::RectangleShape buttonBackground;
		ButtonBgrStatesData buttonBgrData;

		sf::Sound mouseEnteredSound;
		sf::Sound clickSound;

		bool isMouseOn;

		buttonFunc func;

		virtual void BackgroundDataUpdate(bool isSpotted = false);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual bool CheckClick(sf::Vector2f, bool);
	public:
		BaseButton() = default;
		~BaseButton() = default;

		BaseButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, buttonFunc func);
		BaseButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, buttonFunc func,
			const soundData& mouseEnteredSound,
			const soundData& clickSound);



		[[nodiscard]]
		sf::Vector2f getPos() const {
			return buttonBackground.getPosition();
		}

		[[nodiscard]]
		float getScale() const {
			return buttonBackground.getScale().x;
		}

		virtual void setPos(sf::Vector2f newPos) {
			this->buttonBackground.setPosition(newPos);
		}
		virtual void setMouseOutButtonTexture(sf::Texture& newTexture) {
			this->buttonBgrData.mouseOut.texture = &newTexture;
			this->buttonBackground.setTexture(buttonBgrData.mouseOut.texture);
		}
		virtual void setMouseOnButtonTexture(sf::Texture& newTexture) {
			this->buttonBgrData.mouseOn.texture = &newTexture;
		}
		virtual void setButtonTexture(sf::Texture& newTexture) {
			this->buttonBgrData.mouseOn.texture = &newTexture;
			this->buttonBgrData.mouseOut.texture = &newTexture;
		}
		virtual void setScale(float newScale) {
			this->buttonBackground.setScale(newScale, newScale);
		}
		virtual void setMouseEnteredSound(sf::SoundBuffer& newSound) {
			this->mouseEnteredSound.setBuffer(newSound);
		}
		virtual void setClickSound(sf::SoundBuffer& newSound) {
			this->clickSound.setBuffer(newSound);
		}

		virtual void setFunction(buttonFunc newFunc) {
			if (newFunc != nullptr)
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

		void TextInit(const textData& mouseOutText, const textData& mouseOnText, sf::Font& font);
		void TextInit(const textData& mouseOutText, const textData& mouseOnText, sf::Font& font, std::wstring& string);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual bool CheckClick(sf::Vector2f mousePos, bool isClicked);
	public:
		//Constructors
		TextButton() = default;
		~TextButton() = default;

		TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale,
			sf::Font& font, const textData& mouseOutText, const textData& mouseOnText,
			std::wstring string, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, sf::Font& font,
			const textData& mouseOutText, const textData& mouseOnText, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, const rectangleShapeData& data, float scale, sf::Font& font,
			const textData& textData, std::wstring string, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, const rectangleShapeData& data, float scale, sf::Font& font,
			const textData& textData, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale, sf::Font& font,
			const textData& mouseOutText, const textData& mouseOnText, std::wstring string,
			const soundData& mouseEnteredSound, const soundData& clickSound, buttonFunc func = nullptr);

		//Get

		[[nodiscard]]
		int getFontSize() const {
			return buttonText.getCharacterSize();
		}

		[[nodiscard]]
		std::wstring getString() const {
			return buttonText.getString();
		}

		//Set

		void setPos(sf::Vector2f newPos)  override {
			buttonBackground.setPosition(newPos);
			TextPosUpdate();
		}
		void setScale(float newScale) override {
			this->buttonBackground.setScale(newScale, newScale);
			TextPosUpdate();
		}
		void setFont(sf::Font& newFont) {
			buttonText.setFont(newFont);
			TextPosUpdate();
		}
		void setFontSize(int newSize) {
			buttonText.setCharacterSize(newSize);
			TextPosUpdate();
		}
		void setMouseOutButtonColor(sf::Color newColor) {
			mouseOutTxtData.fillColor = newColor;
		}
		void setMouseOnButtonColor(sf::Color newColor) {
			mouseOnTxtData.fillColor = newColor;
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

		ImageButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale, sf::Texture& image,
			float iconScale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, const rectangleShapeData& backgroundData, float buttonScale, sf::Texture& image, float iconScale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale,
			sf::Texture& image, float iconScale, const soundData& mouseEnteredSound, const soundData& clickSound, buttonFunc func = nullptr);
	};


	//////////////////////////////////////////////////////
	//CheckBox

	class SFS_UI_API CheckBox : public ImageButton {
	protected:

		bool isChecked;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		CheckBox() = default;
		~CheckBox() = default;

		CheckBox(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float butttonScale,
			sf::Texture& checkIcon, float iconScale, buttonFunc whenStateChanges = nullptr);

		CheckBox(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float butttonScale,
			sf::Texture& checkIcon, float iconScale, const soundData& mouseEnteredSound, const soundData& clickSound,
			buttonFunc whenStateChanges = nullptr);

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