#pragma once
#ifndef UI_HPP_
#define UI_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include "Base.hpp"
#include "Data.hpp"
#include "Math.hpp"
#include "UIViews.hpp"
#include "framework.h"




namespace SFS {


	//////////////////////////////////////////////////////////////////
	/// Buttons
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//BaseButton

	/// <summary>
	/// Base class for all buttons
	/// </summary>

	class SFS_UI_API BaseButton : public UI {
	protected:
		typedef void(*buttonFunc) ();

		struct ButtonBgrStatesData {
			sf::Texture mouseOn;
			sf::Texture mouseOut;
		};

		sf::Sprite buttonBackground;
		ButtonBgrStatesData buttonBgrData;

		sf::Sound mouseEnteredSound;
		sf::Sound clickSound;

		bool isMouseOn;
		
		buttonFunc func;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual bool CheckClick (sf::Vector2f, bool);
	public:
		BaseButton() = default;
		~BaseButton() = default;

		BaseButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, buttonFunc func);
		BaseButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, buttonFunc func, sf::SoundBuffer& mouseEnteredSound,
			sf::SoundBuffer& clickSound);

		

		[[nodiscard]]
		sf::Vector2f getPos() const  {
			return buttonBackground.getPosition();
		}

		[[nodiscard]]
		int getScale() const {
			return buttonBackground.getScale().x;
		}

		virtual void setPos(sf::Vector2f newPos) {
			buttonBackground.setPosition(newPos);
		}
		virtual void setMouseOutButtonTexture(sf::Texture& newTexture) {
			buttonBgrData.mouseOut = newTexture;
			buttonBackground.setTexture(buttonBgrData.mouseOut);
		}
		virtual void setMouseOnButtonTexture(sf::Texture& newTexture) {
			buttonBgrData.mouseOn = newTexture;
		}
		virtual void setButtonTexture(sf::Texture& newTexture) {
			buttonBgrData.mouseOn = newTexture;
			buttonBgrData.mouseOut = newTexture;
		}
		virtual void setScale(int newScale) {
			this->buttonBackground.setScale(newScale, newScale);
		}
		virtual void setMouseEnteredSound(sf::SoundBuffer& newSound) {
			this->mouseEnteredSound.setBuffer(newSound);
		}
		virtual void setClickSound(sf::SoundBuffer& newSound) {
			this->clickSound.setBuffer(newSound);
		}

		virtual void setFunction(buttonFunc newFunc) {
			this->func = newFunc;
		}

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f & mousePos = sf::Vector2f(0, 0));
	};

	///////////////////////////////////////////
	// TextButton


	/// <summary>
	/// Class for a buttons that have text on it
	/// </summary>

	class SFS_UI_API TextButton : public BaseButton {
	protected:


		sf::Text buttonText;
		textData mouseOutTxtData;
		textData mouseOnTxtData;



		void TextPosUpdate() { buttonText.setPosition(centerText(buttonText, buttonBackground)); }

		void TextDataUpdate(bool isSpotted = false) {
			if (isSpotted) {
				this->buttonText.setCharacterSize(this->mouseOnTxtData.characterSize);
				this->buttonText.setFillColor(this->mouseOnTxtData.fillColor);
				this->buttonText.setOutlineColor(this->mouseOnTxtData.outlineColor);
				this->buttonText.setOutlineThickness(this->mouseOnTxtData.outlineThickness);
			}
			else {
				this->buttonText.setCharacterSize(this->mouseOutTxtData.characterSize);
				this->buttonText.setFillColor(this->mouseOutTxtData.fillColor);
				this->buttonText.setOutlineColor(this->mouseOutTxtData.outlineColor);
				this->buttonText.setOutlineThickness(this->mouseOutTxtData.outlineThickness);
			}
			TextPosUpdate();
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual bool CheckClick(sf::Vector2f mousePos, bool isClicked);
	public:
		//Constructors
		TextButton() = default;
		~TextButton() = default;

		TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
			std::wstring string, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos,sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
			buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, sf::Texture& sprite, int scale, sf::Font& font, textData textData, std::wstring string, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, sf::Texture& sprite, int scale, sf::Font& font, textData textData, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn,int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
			std::wstring string, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, buttonFunc func = nullptr);
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

		void setPos(sf::Vector2f newPos)  override{
			buttonBackground.setPosition(newPos);
			TextPosUpdate();
		}
		void setScale(int newScale) override{
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

		/// <summary>
		/// Draws button
		/// </summary>
		/// <param name="target"></param>
		/// <param name="states"></param>
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

	public:

		ImageButton() = default;

		~ImageButton() = default;

		ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int buttonScale, sf::Texture& image, int iconScale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, sf::Texture& texture, int buttonScale, sf::Texture& image, int iconScale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int buttonScale,sf::Texture& image, int iconScale,sf::SoundBuffer& mouseEnteredSound,
			sf::SoundBuffer& clickSound, buttonFunc func = nullptr);
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

		CheckBox(sf::Vector2f pos, sf::Texture& mouseOutTex, sf::Texture& mouseOnTex, int butttonScale, sf::Texture& checkIcon, int iconScale, buttonFunc whenStateChanges = nullptr);

		CheckBox(sf::Vector2f pos, sf::Texture& mouseOutTex, sf::Texture& mouseOnTex, int butttonScale, sf::Texture& checkIcon, int iconScale, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound,
			buttonFunc whenStateChanges = nullptr);

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));

		[[nodiscard]]
		bool getState() const {
			return this->isChecked;
		}

		void setCheck(bool isChecked) {
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




	///////////////////////////////////////////////////
	/// Button switch
	//////////////////////////////////////////////////


	////////////////////////////////////
	//SwitchOption

	/// <summary>
	/// Single option for a switch
	/// </summary>
	class SFS_UI_API SwitchOption {
	private:
		std::wstring name;
	public:
		SwitchOption() = default;
		~SwitchOption() = default;

		SwitchOption(std::wstring name) : name(name) {
		}

		[[nodiscard]]
		std::wstring getName() const { return name; }

		void setName(std::wstring name) { this->name = name; }
	};

	//////////////////////////////////
	//SwitchEnum

	/// <summary>
	/// Class for a special enums for switch
	/// </summary>

	class SFS_UI_API SwitchStates {
	private:
		std::vector<SwitchOption> options;
		uint8_t actualElement;

	public:
		SwitchStates() = default;
		~SwitchStates() = default;

		SwitchStates(const SwitchStates& original) : options(original.options) { this->actualElement = original.actualElement; }

		void AddOption(const SwitchOption option) {
			this->options.push_back(option);
			if (this->options.size() == 1) {
				this->actualElement = 0;
			}
		}

		void Next() {
			if (this->options.empty()) return;
			if (this->actualElement + 1 < this->options.size())
				this->actualElement++;
			else
				this->actualElement = 0;
		}
		void Last() { 
			if (this->options.empty()) return;
			if (this->actualElement > 0)
				this->actualElement--;
			else
				this->actualElement = this->options.size() - 1; 
		}

		[[nodiscard]]
		SwitchOption getActualOption() const {
			if (this->options.empty()) throw new std::runtime_error("No options aviable");
			return this->options[actualElement];
		}

		[[nodiscard]]
		uint8_t getActualOptionIndex() const  { 
			if (this->options.empty()) throw new std::runtime_error("No options aviable");
			return this->actualElement;
		}

		void setActualOption(uint8_t index) {
			if (this->options.empty()) throw new std::out_of_range("Index out of range");
			if(index < options.size()) actualElement = index; 
		}
	};

	///////////////////////////////////////////
	//Switch

	/// <summary>
	/// Class for a horizontal switch with buttons on left and right
	/// </summary>

	class SFS_UI_API Switch  : public UI{
	public:

		///////////////////////////////////////
		//baseSwitchButton

		/// <summary>
		/// base class for buttons on switch
		/// </summary>

		class SFS_UI_API baseSwitchButton : public UI {
		public:
			enum mode { last, next };
			void setMode(mode newMode) { this->buttonMode = newMode; }

			[[nodiscard]]
			virtual sf::FloatRect getGlobalBounds()const = 0;

			virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override = 0;
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
		protected:
			Switch* owner;

			mode buttonMode;

		};

		//////////////////////////////////////
		//textSwitchButton

		/// <summary>
		/// class for a switch buttons that have text on it
		/// </summary>
		
		class SFS_UI_API textSwitchButton : public baseSwitchButton, public TextButton  {
		public:
			textSwitchButton() = default;

			~textSwitchButton() = default;

			textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
				std::wstring string, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner);

			textSwitchButton(sf::Vector2f pos, sf::Texture& texture, int scale, sf::Font& font, textData textData, std::wstring string, mode buttonMode, Switch* owner);

			textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, textData mouseOutText, textData mouseOnText,
				std::wstring string, mode buttonMode, Switch* owner);

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			[[nodiscard]]
			virtual sf::FloatRect getGlobalBounds() const override;

			virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;

		};

		////////////////////////////////////
		//imageSwitchButton

		/// <summary>
		/// Class for a switch buttons that have icon/image on it
		/// </summary>
		
		class SFS_UI_API imageSwitchButton : public baseSwitchButton, public ImageButton {
		public:
			imageSwitchButton() = default;

			~imageSwitchButton() = default;

			imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int buttonScale, sf::Texture& image, int iconScale, mode buttonMode, Switch* owner);

			imageSwitchButton(sf::Vector2f pos, sf::Texture& texture,int buttonScale, sf::Texture& image, int iconScale, mode buttonMode, Switch* owner);

			imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int buttonScale, sf::Texture& image, int iconScale, sf::SoundBuffer& mouseEnteredSound,
				sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner);
			
			[[nodiscard]]
			virtual sf::FloatRect getGlobalBounds() const override;

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;
		};

		Switch() = default;
		~Switch() = default;

		Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonMouseOutTex,
			sf::Texture& buttonMouseOnTex, int buttonScale, sf::Font& buttonFont, textData buttonMouseOutText, textData buttonMouseOnText,
			sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText, std::wstring rightButtonText, SwitchStates states);

		Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonTex, int buttonScale,
			sf::Font& buttonFont,textData buttonTextData, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText,
			std::wstring rightButtonText, SwitchStates states);

		Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonMouseOutTex,
			sf::Texture& buttonMouseOnTex, int buttonScale, sf::Texture& leftButtonImage, sf::Texture& rightButtonImage,int buttonIconScale, sf::SoundBuffer& buttonSpottedSound,
			sf::SoundBuffer& buttonClickSound, SwitchStates states);

		Switch(sf::Vector2f pos,rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, sf::Texture& buttonTex, int buttonScale,
			sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, int buttonIconScale, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, SwitchStates states);


		[[nodiscard]]
		SwitchOption getActualOption() const { return this->states.getActualOption(); }

		[[nodiscard]]
		uint8_t getActualOptionIndex() const { return this->states.getActualOptionIndex(); }

		[[nodiscard]]
		SwitchStates getOptions() const { return this->states; }

		[[nodiscard]]
		std::wstring getActualText() const { return this->states.getActualOption().getName(); }

		void setActualOption(uint8_t index) {
			this->states.setActualOption(index);
		}

		void setOptions(SwitchStates newOptions) { this->states = newOptions; }

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));

	private:

		sf::RectangleShape background;
		std::shared_ptr<baseSwitchButton> leftButton;
		std::shared_ptr<baseSwitchButton> rightButton;
		sf::Text text;
		SwitchStates states;

		void UpdateText();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	};









	///////////////////////////////////////////
	///Text box

	/// <summary>
	/// Class of text box.
	/// </summary>

	class SFS_UI_API TextBox : public UI {
	private:
		sf::Text text;
		sf::RectangleShape background;
		bool isChecked;

		rectangleShapeData notActiveTextBoxData;
		rectangleShapeData activeTextBoxData;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		TextBox() = default;
		~TextBox() = default;

		TextBox(sf::Vector2f pos, rectangleShapeData boxData, rectangleShapeData activeBoxData, textData textData, sf::Font& font);

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;

		[[nodiscard]]
		sf::String getText() const {
			return this->text.getString();
		}

		[[nodiscard]]
		bool getChecked() const {
			return this->isChecked;
		}

		void setText(sf::String newText) {
			this->text.setString(newText);
		}

		void setChecked(bool newState) {
			this->isChecked = newState;
		}
	};

	////////////////////////////////////////
	//toolTip

	class SFS_UI_API toolTip : public UI {
	private:
		sf::RectangleShape background;
		ClippedView<sf::Text> Text;
		sf::FloatRect fieldWhenActive;
		bool isVisible;

		std::optional<sf::Time> mouseOverTime;
		std::optional<sf::Time> requiredMouseOverTime;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:

		toolTip() = default;
		~toolTip() = default;
		toolTip(rectangleShapeData backgroundData, textData tipTextData, sf::Vector2f pos, std::wstring text, sf::Font& textFont, sf::FloatRect fieldWhenVisible,
			sf::Time timeToActivate = sf::Time::Zero);

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;
	};

}

#endif
