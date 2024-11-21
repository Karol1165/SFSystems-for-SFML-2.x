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

	sf::Vector2f centerText(const sf::Text& text, const sf::Sprite& button) {
		sf::FloatRect textRect = text.getLocalBounds();
		return sf::Vector2f(button.getPosition().x + (button.getGlobalBounds().width - textRect.width) / 2.0f - textRect.left,
			button.getPosition().y + (button.getGlobalBounds().height - textRect.height) / 2.0f - textRect.top);
	}

	sf::Vector2f centerText(const sf::Text& text, const sf::RectangleShape& shape) {
		sf::FloatRect textRect = text.getLocalBounds();
		return sf::Vector2f(shape.getPosition().x + (shape.getGlobalBounds().width - textRect.width) / 2.0f - textRect.left,
			shape.getPosition().y + (shape.getGlobalBounds().height - textRect.height) / 2.0f - textRect.top);
	}

	sf::Vector2f centerText(const sf::Text& text, const sf::FloatRect& bounds) {
		sf::FloatRect textRect = text.getLocalBounds();
		return sf::Vector2f(bounds.getPosition().x + (bounds.width - textRect.width) / 2.0f - textRect.left,
			bounds.getPosition().y + (bounds.height - textRect.height) / 2.0f - textRect.top);
	}

	sf::Vector2f centerSprite(const sf::Sprite& spriteToCenter, const sf::Sprite& referenceSprite) {
		float xPos = referenceSprite.getPosition().x + (referenceSprite.getLocalBounds().width - spriteToCenter.getLocalBounds().width) / 2;
		float yPos = referenceSprite.getPosition().y + (referenceSprite.getLocalBounds().height - spriteToCenter.getLocalBounds().height) / 2;

		return sf::Vector2f(xPos, yPos);
	}

	sf::Vector2f centerSprite(const sf::Sprite& spriteToCenter, const sf::FloatRect& bounds) {
		float xPos = bounds.getPosition().x + (bounds.width - spriteToCenter.getLocalBounds().width) / 2;
		float yPos = bounds.getPosition().y + (bounds.height - spriteToCenter.getLocalBounds().height) / 2;

		return sf::Vector2f(xPos, yPos);
	}

}