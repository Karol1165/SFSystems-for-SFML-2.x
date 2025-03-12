#include "pch.h"
#include "ToolTip.hpp"

namespace SFS {
	////////////////////////////////////////
	//toolTip

	toolTip::toolTip(rectangleShapeData backgroundData, textData tipTextData, sf::Vector2f pos, std::wstring text, sf::Font& textFont, sf::FloatRect fieldWhenVisible,
		sf::Time timeToActivate) {
		sf::Text tipText;
		setRectangleData(backgroundData, this->background);
		setTextData(tipTextData, tipText);
		this->background.setPosition(pos);
		this->fieldWhenActive = fieldWhenVisible;
		tipText.setFont(textFont);
		tipText.setString(text);
		tipText.setPosition(centerText(tipText, background));

		this->Text.setObject(new sf::Text(tipText));
		this->Text.setBounds(background.getGlobalBounds());

		if (timeToActivate != sf::Time::Zero) {
			this->requiredCursorOverTime = timeToActivate;
			this->cursorOverTime = sf::Time::Zero;
		}

		this->isVisible = false;
	}

	void toolTip::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (!this->requiredCursorOverTime.has_value())
			this->isVisible = this->fieldWhenActive.contains(mousePos);
		else {
			if (this->fieldWhenActive.contains(mousePos)) {
				*this->cursorOverTime += deltaTime;
				if (*this->cursorOverTime > *this->requiredCursorOverTime)
					this->isVisible = true;
				else
					this->isVisible = false;
			}
			else {
				*this->cursorOverTime = sf::Time::Zero;
				this->isVisible = false;
			}
		}
	}

	void toolTip::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (isVisible) {
			target.draw(this->background, states);
			target.draw(this->Text, states);
		}
	}
}