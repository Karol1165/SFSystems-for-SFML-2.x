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

}

#endif