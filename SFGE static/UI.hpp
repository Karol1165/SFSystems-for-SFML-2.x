#pragma once
#ifndef UI_HPP_
#define UI_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Components.hpp"
#include "Math.hpp"

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
	class ImageButton : public BaseButton {
	private:
		sf::Sprite buttonImage;

		virtual void draw(sf::RenderTarget& target)const;

	public:



		ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn,sf::Texture& image, int scale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, sf::Texture& texture,sf::Texture& image, int scale, buttonFunc func = nullptr);

		ImageButton(sf::Vector2f pos, sf::Texture& mouseOut, sf::Texture& mouseOn,sf::Texture& image, int scale,sf::SoundBuffer& mouseEnteredSound,
			sf::SoundBuffer& clickSound, buttonFunc func = nullptr);
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
		std::wstring getName() const { return name; }

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
		SwitchOption getActualOption() const { return this->options[actualElement]; }

		[[nodiscard]]
		uint8_t getActualOptionIndex() const  { return this->actualElement; }

		void setActualOption(uint8_t index) { if(index < options.size()) actualElement = index; }
	};

	class Switch  : public UI{
	public:
		static class baseSwitchButton : public UI {
		public:
			enum mode { last, next };
			void setMode(mode newMode) { this->buttonMode = newMode; }
			virtual void CheckStatus(const sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override = 0;
		protected:
			Switch* owner;

			mode buttonMode;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
		};
		static class textSwitchButton : public baseSwitchButton, public TextButton  {
		public:
			textSwitchButton() = default;
			~textSwitchButton() = default;

		};
		static class imageSwitchButton : public baseSwitchButton, public ImageButton {
		public:
			imageSwitchButton() = default;
			~imageSwitchButton() = default;
		};

		Switch() = default;
		~Switch() = default;

		Switch(sf::RectangleShape background, baseSwitchButton* leftButton, baseSwitchButton* rightButton, SwitchEnum states);
		Switch(sf::RectangleShape background, baseSwitchButton* leftButton, baseSwitchButton* rightButton);

		[[nodiscard]]
		SwitchOption getActualOption() { return this->states.getActualOption(); }

		[[nodiscard]]
		uint8_t getActualOptionIndex() { return this->states.getActualOptionIndex(); }

		[[nodiscard]]
		SwitchEnum getOptions() { return this->states; }

		[[nodiscard]]
		std::wstring getActualText() { return this->states.getActualOption().getName(); }

		void setOptions(SwitchEnum newOptions) { this->states = newOptions; }

		virtual void CheckStatus(const sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));

	private:
		sf::RectangleShape background;
		std::shared_ptr<baseSwitchButton> leftButton;
		std::shared_ptr<baseSwitchButton> rightButton;
		sf::Text text;
		SwitchEnum states;

		void UpdateText();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

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