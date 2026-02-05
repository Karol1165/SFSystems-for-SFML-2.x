#include "pch.h"
#include "TextBox.hpp"

namespace SFS {
	////////////////////////////////////////////
	//TextBox


	TextBox::TextBox(sf::Vector2f pos, rectangleShapeData boxData, rectangleShapeData activeBoxData, textData textData) : isChecked(false) {
		this->notActiveTextBoxData = boxData;
		this->activeTextBoxData = activeBoxData;

		this->background.setPosition(pos);
		setRectangleData(notActiveTextBoxData, this->background);

		setTextData(textData, this->text);

		this->textView.setObject(&this->text);
		this->textView.setBounds(this->background.getGlobalBounds());
	}

	void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(background, states);
		target.draw(textView, states);
	}

	void TextBox::CheckStatus(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		if (e.type == sf::Event::MouseButtonPressed) {
			if (e.mouseButton.button == sf::Mouse::Left) {
				if (background.getGlobalBounds().contains(mousePos)) {
					textBoxUpdate(true);
					isChecked = true;
					// Mark event as technical to avoid further processing
					markEventAsTechnical(e);
				}
				else {
					isChecked = false;
					textBoxUpdate(false);
				}
			}
		}
		if (isChecked && e.type == sf::Event::TextEntered) {
			if (e.text.unicode == 8) { // Handle backspace
				std::wstring str = static_cast<std::wstring>(text.getString());
				if (!str.empty()) {
					str.pop_back();
					text.setString(sf::String(str));
				}
			}
			else if (e.text.unicode >= 32 && e.text.unicode != 127) {
				text.setString(text.getString() + static_cast<wchar_t>(e.text.unicode));
			}

			this->text.setPosition(centerText(this->text, this->background));


		}
	}
}