#pragma once
#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include "framework.h"
#include "Data.hpp"
#include "Base.hpp"
#include <SFML/Graphics.hpp>
#include "UIViews.hpp"
#include "Math.hpp"

namespace SFS {

	///////////////////////////////////////////
	///Text box

/// <summary>
/// Class of text box.
/// </summary>

	class SFS_UI_API TextBox : public UI {
	private:
		sf::Text text;
		ClippedView textView;
		sf::RectangleShape background;
		bool isChecked = false;

		rectangleShapeData notActiveTextBoxData;
		rectangleShapeData activeTextBoxData;

		void textBoxUpdate(bool isActive = false) {
			if (isActive)
				setRectangleData(activeTextBoxData, this->background);
			else
				setRectangleData(notActiveTextBoxData, this->background);

			this->text.setPosition(centerText(this->text, this->background));
			this->textView.setBounds(this->background.getGlobalBounds());
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		TextBox() = default;
		~TextBox() = default;

		TextBox(sf::Vector2f pos, rectangleShapeData boxData, rectangleShapeData activeBoxData, textData textData);

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

}

#endif