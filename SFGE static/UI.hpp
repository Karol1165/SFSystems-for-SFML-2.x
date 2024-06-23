#pragma once
#ifndef UI_HPP_
#define UI_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Components.hpp"
#include "Math.hpp"
#ifdef _DEBUG
#include<iostream>
#endif
namespace SFGF {




	//////////////////////////////////////////////////////////////////
	/// Buttons
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//BaseButton

	/// <summary>
	/// Base class for all buttons
	/// </summary>

	class BaseButton : public UI, public Clickable {
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
		sf::Vector2f getPos()  {
			return buttonBackground.getPosition();
		}

		[[nodiscard]]
		int getScale() {
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

		virtual void CheckStatus(const sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f & mousePos = sf::Vector2f(0, 0));
	};

	///////////////////////////////////////////
	// TextButton


	/// <summary>
	/// Class for a buttons that have text on it
	/// </summary>

	class TextButton : public BaseButton {
	protected:
		struct ButtonTxtStatesData {
			sf::Color mouseOn;
			sf::Color mouseOut;
		};


		sf::Text buttonText;
		ButtonTxtStatesData buttonTxtData;



		void TextPosUpdate() { buttonText.setPosition(centerText(buttonText, buttonBackground)); }

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual bool CheckClick(sf::Vector2f mousePos, bool isClicked);
	public:
		//Constructors
		TextButton() = default;
		~TextButton() = default;

		TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
			std::wstring string, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos,sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
			buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, sf::Texture& sprite, int scale, sf::Font& font, int fontSize, sf::Color color, std::wstring string, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, sf::Texture& sprite, int scale, sf::Font& font, int fontSize, sf::Color color, buttonFunc func = nullptr);

		TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn,int scale, sf::Font& font,int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
			std::wstring string, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, buttonFunc func = nullptr);
		//Get

		[[nodiscard]]
		int getFontSize() {
			return buttonText.getCharacterSize();
		}

		[[nodiscard]]
		std::wstring getString() {
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
			buttonTxtData.mouseOut = newColor;
			buttonText.setFillColor(buttonTxtData.mouseOut);
		}
		void setMouseOnButtonColor(sf::Color newColor) {
			buttonTxtData.mouseOn = newColor;
		}
		void setString(std::wstring newString) {
			buttonText.setString(newString);
			TextPosUpdate();
		}

		//Check Status

	};

	///////////////////////////////////////////////////
	//ImageButton

	/// <summary>
	/// Class for buttons that have icon/image on it
	/// </summary>

	class ImageButton : public BaseButton {
	private:
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

		ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn,sf::Texture& image, int scale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, sf::Texture& texture,sf::Texture& image, int scale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn,sf::Texture& image, int scale,sf::SoundBuffer& mouseEnteredSound,
			sf::SoundBuffer& clickSound, buttonFunc func = nullptr);
	};

	///////////////////////////////////////////////////
	/// Button switch
	//////////////////////////////////////////////////


	template <typename T>
	class TrackedVector : public std::vector<T> {
	public:
		using std::vector<T>::vector; // Inherit constructors

		void push_back(const T& value) {
			std::vector<T>::push_back(value);
			std::cout << "Element added, new size: " << this->size() << "\n";
		}

		void push_back(T&& value) {
			std::vector<T>::push_back(std::move(value));
			std::cout << "Element added (move), new size: " << this->size() << "\n";
		}

		void pop_back() {
			std::vector<T>::pop_back();
			std::cout << "Element removed, new size: " << this->size() << "\n";
		}

		void clear() {
			std::vector<T>::clear();
			std::cout << "All elements removed, new size: " << this->size() << "\n";
		}

		bool empty() {
			std::cout << "vector size: " << this->size() << "\n";
			bool result = std::vector<T>::empty();
			std::cout << "checked is vector empty, result: " << result << "\n";
			return result;
		}

		// Implement other modifying methods similarly if needed
	};

	////////////////////////////////////
	//SwitchOption

	/// <summary>
	/// Single option for a switch
	/// </summary>
	class SwitchOption {
	private:
		std::wstring name;
	public:
		SwitchOption() = default;
		~SwitchOption() = default;

		SwitchOption(std::wstring name) : name(name) {
#ifdef _DEBUG
			std::wcout << "switchOption constructed: " << name << "\n";
#endif
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

	class SwitchStates {
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

	class Switch  : public UI{
	public:

		///////////////////////////////////////
		//baseSwitchButton

		/// <summary>
		/// base class for buttons on switch
		/// </summary>

		class baseSwitchButton : public UI {
		public:
			enum mode { last, next };
			void setMode(mode newMode) { this->buttonMode = newMode; }
			virtual sf::FloatRect getGlobalBounds()const = 0;
			virtual void CheckStatus(const sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override = 0;
		private:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override  {}
		protected:
			Switch* owner;

			mode buttonMode;

		};

		//////////////////////////////////////
		//textSwitchButton

		/// <summary>
		/// class for a switch buttons that have text on it
		/// </summary>
		
		class textSwitchButton : public baseSwitchButton, public TextButton  {
		public:
			textSwitchButton() = default;

			~textSwitchButton() = default;

			textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
				std::wstring string, sf::SoundBuffer& mouseEnteredSound, sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner);

			textSwitchButton(sf::Vector2f pos, sf::Texture& texture, int scale, sf::Font& font, int fontSize, std::wstring string, sf::Color color, mode buttonMode, Switch* owner);

			textSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
				std::wstring string, mode buttonMode, Switch* owner);

			virtual sf::FloatRect getGlobalBounds() const override;

			virtual void CheckStatus(const sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;

		};

		////////////////////////////////////
		//imageSwitchButton

		/// <summary>
		/// Class for a switch buttons that have icon/image on it
		/// </summary>
		
		class imageSwitchButton : public baseSwitchButton, public ImageButton {
		public:
			imageSwitchButton() = default;

			~imageSwitchButton() = default;

			imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, sf::Texture& image, int scale, mode buttonMode, Switch* owner);

			imageSwitchButton(sf::Vector2f pos, sf::Texture& texture, sf::Texture& image, int scale, mode buttonMode, Switch* owner);

			imageSwitchButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, sf::Texture& image, int scale, sf::SoundBuffer& mouseEnteredSound,
				sf::SoundBuffer& clickSound, mode buttonMode, Switch* owner);

			virtual sf::FloatRect getGlobalBounds() const override;

			virtual void CheckStatus(const sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;
		};

		Switch() = default;
		~Switch() = default;

		Switch(sf::Vector2f pos, sf::Color backgroundColor, int backgroundRectLength, sf::Color textColor, sf::Font& textFont, int textFontSize, sf::Texture& buttonMouseOutTex,
			sf::Texture& buttonMouseOnTex, int buttonScale, sf::Font& buttonFont, int buttonFontSize, sf::Color buttonMouseOutColor, sf::Color buttonMouseOnColor,
			sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText, std::wstring rightButtonText, SwitchStates states);

		Switch(sf::Vector2f pos, sf::Color backgroundColor, int backgroundRectLength, sf::Color textColor, sf::Font& textFont, int textFontSize, sf::Texture& buttonTex, int buttonScale,
			sf::Font& buttonFont, int buttonFontSize, sf::Color buttonColor, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, std::wstring leftButtonText,
			std::wstring rightButtonText, SwitchStates states);

		Switch(sf::Vector2f pos, sf::Color backgroundColor, int backgroundRectLength, sf::Color textColor, sf::Font& textFont, int textFontSize, sf::Texture& buttonMouseOutTex,
			sf::Texture& buttonMouseOnTex, int buttonScale, sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, int buttonImageScale, sf::SoundBuffer& buttonSpottedSound,
			sf::SoundBuffer& buttonClickSound, SwitchStates states);

		Switch(sf::Vector2f pos, sf::Color backgroundColor, int backgroundRectLength, sf::Color textColor, sf::Font& textFont, int textFontSize, sf::Texture& buttonTex, int buttonScale,
			sf::Texture& leftButtonImage, sf::Texture& rightButtonImage , int buttonImageScale, sf::SoundBuffer& buttonSpottedSound, sf::SoundBuffer& buttonClickSound, SwitchStates states);


		[[nodiscard]]
		SwitchOption getActualOption() { return this->states.getActualOption(); }

		[[nodiscard]]
		uint8_t getActualOptionIndex() { return this->states.getActualOptionIndex(); }

		[[nodiscard]]
		SwitchStates getOptions() { return this->states; }

		[[nodiscard]]
		std::wstring getActualText() { return this->states.getActualOption().getName(); }

		void setOptions(SwitchStates newOptions) { this->states = newOptions; }

		virtual void CheckStatus(const sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));

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

	class TextBox : public UI {

	};

	/////////////////////////////////////////////
	///Views
	////////////////////////////////////////////

	////////////////////////////////////////////
	//ScroolView

	/// <summary>
	/// Class of ScroolView
	/// </summary>

	class ScroolView : public UI {
	private:
		std::vector<UI> elements;
		sf::View view;
		sf::RectangleShape scroolBackground;
		sf::CircleShape scroolCircle;
	public:
		ScroolView() = default;
		~ScroolView() = default;

	};

	///Other

	class GameDialog : public UI {

	};

}

#endif