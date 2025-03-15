#pragma once
#ifndef SWITCH_HPP_
#define SWITCH_HPP_

#include "framework.h"
#include "Base.hpp"
#include "Data.hpp"
#include "Button.hpp"
#
namespace SFS {
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
	//SwitchStates

	/// <summary>
	/// Class for a special enums for switch
	/// </summary>

	class SFS_UI_API SwitchStates {
	private:
		std::vector<SwitchOption> options;
		uint8_t currentElement;

	public:
		SwitchStates() = default;
		~SwitchStates() = default;

		SwitchStates(const SwitchStates& original) : options(original.options) { this->currentElement = original.currentElement; }

		void AddOption(const SwitchOption option) {
			this->options.push_back(option);
			if (this->options.size() == 1) {
				this->currentElement = 0;
			}
		}

		void Next() {
			if (this->options.empty()) return;
			if (this->currentElement + 1 < this->options.size())
				this->currentElement++;
			else
				this->currentElement = 0;
		}
		void Last() {
			if (this->options.empty()) return;
			if (this->currentElement > 0)
				this->currentElement--;
			else
				this->currentElement = this->options.size() - 1;
		}

		[[nodiscard]]
		SwitchOption getCurrentOption() const {
			if (this->options.empty()) throw new std::runtime_error("No options aviable");
			return this->options[currentElement];
		}

		[[nodiscard]]
		uint8_t getCurrentOptionIndex() const {
			if (this->options.empty()) throw new std::runtime_error("No options aviable");
			return this->currentElement;
		}

		void setCurrentOption(uint8_t index) {
			if (this->options.empty()) throw new std::out_of_range("Index out of range");
			if (index < options.size()) currentElement = index;
		}
	};

	///////////////////////////////////////////
	//Switch

	/// <summary>
	/// Class for a horizontal switch with buttons on left and right
	/// </summary>

	class SFS_UI_API Switch : public UI {
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
			virtual sf::FloatRect getGlobalBounds() const = 0;

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

		class SFS_UI_API textSwitchButton : public baseSwitchButton, public TextButton {
		public:
			textSwitchButton() = default;

			~textSwitchButton() = default;

			textSwitchButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale,
				sf::Font& font, textData mouseOutText, textData mouseOnText,
				std::wstring string, const soundData& mouseEnteredSound, const soundData& clickSound, mode buttonMode, Switch* owner);

			textSwitchButton(sf::Vector2f pos, const rectangleShapeData& data, float scale, sf::Font& font, textData textData,
				std::wstring string, mode buttonMode, Switch* owner);

			textSwitchButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float scale,
				sf::Font& font, textData mouseOutText, textData mouseOnText,
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

			imageSwitchButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale,
				sf::Texture& image, float iconScale, mode buttonMode, Switch* owner);

			imageSwitchButton(sf::Vector2f pos, const rectangleShapeData& data, float buttonScale,
				sf::Texture& image, float iconScale, mode buttonMode, Switch* owner);

			imageSwitchButton(sf::Vector2f pos, const rectangleShapeData& mouseOut, const rectangleShapeData& mouseOn, float buttonScale,
				sf::Texture& image, float iconScale, const soundData& mouseEnteredSound,
				const soundData& clickSound, mode buttonMode, Switch* owner);

			[[nodiscard]]
			virtual sf::FloatRect getGlobalBounds() const override;

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;
		};

		Switch() = default;
		~Switch() = default;

		Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData,
			const rectangleShapeData& buttonMouseOut, const rectangleShapeData& buttonMouseOn, float buttonScale,
			sf::Font& buttonFont, textData buttonMouseOutText, textData buttonMouseOnText,
			const soundData& buttonSpottedSound, const soundData& buttonClickSound, std::wstring leftButtonText, std::wstring rightButtonText,
			SwitchStates states);

		Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, const rectangleShapeData& buttonData,
			float buttonScale, sf::Font& buttonFont, textData buttonTextData, 
			std::wstring leftButtonText, std::wstring rightButtonText, SwitchStates states);

		Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData,
			const rectangleShapeData& buttonMouseOut, const rectangleShapeData& buttonMouseOn, float buttonScale,
			sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, float buttonIconScale, const soundData& buttonSpottedSound,
			const soundData& buttonClickSound, SwitchStates states);

		Switch(sf::Vector2f pos, rectangleShapeData backgroundData, sf::Font& textFont, textData optionTextData, const rectangleShapeData& buttonTex,
			float buttonScale, sf::Texture& leftButtonImage, sf::Texture& rightButtonImage, float buttonIconScale,
			 SwitchStates states);


		[[nodiscard]]
		SwitchOption getCurrentOption() const { return this->states.getCurrentOption(); }

		[[nodiscard]]
		uint8_t getCurrentOptionIndex() const { return this->states.getCurrentOptionIndex(); }

		[[nodiscard]]
		SwitchStates getOptions() const { return this->states; }

		[[nodiscard]]
		std::wstring getCurrentText() const { return this->states.getCurrentOption().getName(); }

		void setCurrentOption(uint8_t index) {
			this->states.setCurrentOption(index);
		}

		void setOptions(SwitchStates newOptions) { this->states = newOptions; }

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));

	private:

		void optionTextInit(const SwitchStates& states, const sf::Font& font, const textData& data);

		sf::RectangleShape background;
		ptr<baseSwitchButton> leftButton;
		ptr<baseSwitchButton> rightButton;
		sf::Text text;
		ClippedView textView;
		SwitchStates states;
		void UpdateText();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	};
}

#endif
