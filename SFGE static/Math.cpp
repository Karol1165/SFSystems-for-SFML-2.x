#include "pch.h"
#include "Math.hpp"

namespace SFGF {

	double Angle_Between_Points(sf::Vector2f a, sf::Vector2f b) {
		double A, B, C;
		A = a.x - b.x;
		B = a.y - b.y;
		C = std::pow(A * A + B * B, 0.5);
		return std::asin(A / C) * M_RADIANS_TO_DEGREES_CONVERTER;
	}

	sf::Vector2f centerText(const sf::Text& Text, const sf::Sprite& button) {
		sf::FloatRect textRect = Text.getLocalBounds();
		return sf::Vector2f(button.getPosition().x + (button.getGlobalBounds().width - textRect.width) / 2.0f - textRect.left,
			button.getPosition().y + (button.getGlobalBounds().height - textRect.height) / 2.0f - textRect.top);
	}

	sf::Vector2f centerSprite(sf::Sprite& spriteToCenter, sf::Sprite& referenceSprite) {
		float xPos = referenceSprite.getPosition().x + (referenceSprite.getLocalBounds().width - spriteToCenter.getLocalBounds().width) / 2;
		float yPos = referenceSprite.getPosition().y + (referenceSprite.getLocalBounds().height - spriteToCenter.getLocalBounds().height) / 2;

		return sf::Vector2f(xPos, yPos);
	}

}