#pragma once
#ifndef SWITCH_HPP_
#define SWITCH_HPP_

#include "framework.h"

#include "Button.hpp"
#
namespace SFS {


// Single option for a switch
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




	//Class for a special enums for switch

	class SFS_UI_API SwitchStates {
	private:
		std::vector<SwitchOption> options;
		size_t currentElement = 0;

	public:
		SwitchStates() = default;
		~SwitchStates() = default;

		SwitchStates(const SwitchStates& original) : options(original.options) { this->currentElement = original.currentElement; }

		void AddOption(const SwitchOption& option) {
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
		size_t getCurrentOptionIndex() const {
			if (this->options.empty()) throw new std::runtime_error("No options aviable");
			return this->currentElement;
		}

		void setCurrentOption(size_t index) {
			if (this->options.empty()) throw new std::out_of_range("Index out of range");
			if (index < options.size()) currentElement = index;
		}
	};

	/// Class for a horizontal switch with buttons on left and right

	class SFS_UI_API Switch : public UI {
	public:

		// base class for buttons on switch

		class SFS_UI_API baseSwitchButton : public UI {
		public:
			enum class mode { last, next };
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

		// class for a switch buttons that have text on it

		class SFS_UI_API textSwitchButton : public baseSwitchButton, public TextButton {
		public:
			textSwitchButton() = default;

			~textSwitchButton() = default;

			textSwitchButton(const sf::Vector2f& pos, const TextButton::StyleData& style, const sf::String& string,
				 mode buttonMode, Switch* owner);

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			[[nodiscard]]
			virtual sf::FloatRect getGlobalBounds() const override;

			virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;

		};


		// Class for a switch buttons that have icon/image on it

		class SFS_UI_API imageSwitchButton : public baseSwitchButton, public ImageButton {
		public:

			imageSwitchButton() = default;
			~imageSwitchButton() = default;

			imageSwitchButton(const sf::Vector2f& pos, const ImageButton::StyleData& style,
				sf::Texture& image, mode buttonMode, Switch* owner);

			[[nodiscard]]
			virtual sf::FloatRect getGlobalBounds() const override;

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

			virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;
		};

		Switch() = default;
		~Switch() = default;

		Switch(const sf::Vector2f& pos, const rectangleShapeData& backgroundData, const textData& optionTextData,
			const TextButton::StyleData& btnStyle, const sf::String& leftButtonText, const sf::String& rightButtonText,
			SwitchStates states);

		Switch(const sf::Vector2f& pos, const rectangleShapeData& backgroundData, const textData& optionTextData,
			const ImageButton::StyleData& btnStyle, sf::Texture& leftButtonImage, sf::Texture& rightButtonImage,
			SwitchStates states);

		[[nodiscard]]
		SwitchOption getCurrentOption() const { return this->states.getCurrentOption(); }

		[[nodiscard]]
		size_t getCurrentOptionIndex() const { return this->states.getCurrentOptionIndex(); }

		[[nodiscard]]
		SwitchStates getOptions() const { return this->states; }

		[[nodiscard]]
		std::wstring getCurrentText() const { return this->states.getCurrentOption().getName(); }

		void setCurrentOption(size_t index) {
			this->states.setCurrentOption(index);
		}

		void setOptions(SwitchStates newOptions) { this->states = newOptions; }

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0));

	private:

		void optionTextInit(const SwitchStates& states, const textData& data);

		sf::RectangleShape background;
		sptr<baseSwitchButton> leftButton;
		sptr<baseSwitchButton> rightButton;
		sf::Text text;
		ClippedView textView;
		SwitchStates states;
		void UpdateText();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	};
}

#endif
