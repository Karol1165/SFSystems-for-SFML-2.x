#pragma once
#ifndef UI_HPP_
#define UI_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Components.hpp"
#include "Math.hpp"

namespace SFGF {

	/// <summary>
	/// Base class for all UI elements
	/// </summary>

	class UI : public sf::Drawable {
	public:
		virtual void CheckStatus(sf::Vector2f& mousePos, bool isLeftMousePressed, bool isRightMousePressed) {}
	};

	//////////////////////////////////////////////////////////////////
	/// Buttons
	/////////////////////////////////////////////////////////////////

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
		virtual void setMouseEnteredSound(sf::Sound& newSound) {
			this->mouseEnteredSound = newSound;
		}
		virtual void setClickSound(sf::Sound& newSound) {
			this->clickSound = newSound;
		}
	};

	class TextButton : public BaseButton {
	private:
		struct ButtonTxtStatesData {
			sf::Color mouseOn;
			sf::Color mouseOut;
		};


		sf::Text buttonText;
		ButtonTxtStatesData buttonTxtData;



		void TextPosUpdate() { buttonText.setPosition(centerText(buttonText, buttonBackground)); }

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
			target.draw(buttonBackground);
			target.draw(buttonText);
		}

		virtual bool CheckClick(sf::Vector2f mousePos, bool isClicked);
	public:
		//Constructors
		TextButton() = default;
		~TextButton() = default;
		template <typename F>
		TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
			std::wstring string, F func);
		template<typename F>
		TextButton(sf::Vector2f pos,sf::Texture& mouseOut, sf::Texture& mouseOn, int scale, sf::Font& font, int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
			F func);
		template<typename F>
		TextButton(sf::Vector2f pos, sf::Texture& sprite, int scale, sf::Font& font, int fontSize, sf::Color color, std::wstring string, F func);
		template<typename F>
		TextButton(sf::Vector2f pos, sf::Texture& sprite, int scale, sf::Font& font, int fontSize, sf::Color color, F func);
		template<typename F>
		TextButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn,int scale, sf::Font& font,int fontSize, sf::Color mouseOutColor, sf::Color mouseOnColor,
			std::wstring string, sf::Sound& mouseEnteredSound, sf::Sound& clickSound, F func);
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
		virtual void CheckStatus(sf::Vector2f& mousePos, bool isLeftMousePressed, bool isRightMousePressed);
	};
	class ImageButton : public BaseButton {
	private:
		sf::Sprite buttonImage;

		virtual void draw(sf::RenderTarget& target)const;

	public:
		virtual void CheckStatus(sf::Vector2f mousePos, bool isLeftMousePressed, bool isRightMousePressed);

		template<typename F>
		ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn,sf::Texture& image, int scale, F func);
		template<typename F>
		ImageButton(sf::Vector2f pos, sf::Texture& texture,sf::Texture& image, int scale, F func);
		template<typename F>
		ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn,sf::Texture& image, int scale,sf::Sound& mouseEnteredSound,sf::Sound& clickSound, F func);
	};

	///////////
	/// Button switch
	///////////

	class SwitchOption {
	private:
		std::wstring name;
	public:
		SwitchOption() = default;
		~SwitchOption() = default;

		SwitchOption(std::wstring name) : name(name) {}

		[[nodiscard]]
		std::wstring getName() { return name; }

		void setName(std::wstring name) { this->name = name; }
	};

	class SwitchEnum {
	private:
		std::vector<SwitchOption> options;
		uint8_t actualElement;

	public:
		SwitchEnum() { actualElement = 0; }
		~SwitchEnum() = default;

		SwitchEnum(const SwitchEnum& original) : options(original.options), actualElement(original.actualElement) {}

		void AddOption(const SwitchOption& option) { this->options.push_back(option); }

		void Next() { if (actualElement + 1 < options.size()) actualElement++; else actualElement = 0; }
		void Last() { if (actualElement > 0) actualElement--; else actualElement = options.size() - 1;}

		[[nodiscard]]
		SwitchOption getActualOption() { return this->options[actualElement]; }

		void setActualOption(uint8_t index) { if(index < options.size()) actualElement = index; }
	};

	class Switch  : public UI{
	private:
		sf::RectangleShape background;
		TextButton leftButton;
		TextButton rightButton;
		sf::Text text;
		SwitchEnum states;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	public:
		Switch() = default;
		~Switch() = default;

		Switch(sf::RectangleShape background, TextButton leftButton, TextButton rightButton, SwitchEnum states);
		Switch(sf::RectangleShape background, TextButton leftButton, TextButton rightButton);

		[[nodiscard]]
		SwitchOption getActualOption() { return this->states.getActualOption(); }

		[[nodiscard]]
		SwitchEnum getOptions() { return this->states; }

		[[nodiscard]]
		std::wstring getActualText() { return this->states.getActualOption().getName(); }

		void setOptions(SwitchEnum newOptions) { this->states = newOptions; }
	};

	///Text box

	/// <summary>
	/// Class of text box.
	/// </summary>

	class TextBox : public UI {

	};

	///Views

	/// <summary>
	/// Class of ScroolView
	/// </summary>

	class ScroolView : public UI {
	private:
		std::vector<UI> elements;
		sf::View view;
	public:
		ScroolView() = default;
		~ScroolView() = default;

	};

	///Other

	class GameDialog : public UI {

	};

}

#endif