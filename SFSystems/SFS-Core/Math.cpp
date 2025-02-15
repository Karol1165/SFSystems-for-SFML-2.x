#include "pch.h"
#include "Math.hpp"

namespace SFS {

	double Angle_Between_Points(sf::Vector2f a, sf::Vector2f b) {
		double A, B, C;
		A = a.x - b.x;
		B = a.y - b.y;
		C = std::pow(A * A + B * B, 0.5);
		return std::asin(A / C) * M_RADIANS_TO_DEGREES_CONVERTER;
	}

	sf::Vector2f center(const sf::FloatRect& boundsToCenter, const sf::FloatRect& background) {
		return sf::Vector2f(background.getPosition().x + (background.width - boundsToCenter.width) / 2.0f,
			background.getPosition().y + (background.height - boundsToCenter.height) / 2.0f);
	}

	sf::Vector2f centerText(const sf::Text& text, const sf::Sprite& sprite) {
		sf::FloatRect textRect = text.getLocalBounds();
		return sf::Vector2f(sprite.getPosition().x + (sprite.getGlobalBounds().width - textRect.width) / 2.0f - textRect.left,
			sprite.getPosition().y + (sprite.getGlobalBounds().height - textRect.height) / 2.0f - textRect.top);
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

	sf::Vector2f centerSprite(const sf::Sprite& spriteToCenter, const sf::FloatRect& bounds) {
		return sf::Vector2f(center(spriteToCenter.getGlobalBounds(), bounds));
	}

	sf::Vector2f centerSprite(const sf::Sprite& spriteToCenter, const sf::Sprite& referenceSprite) {
		return sf::Vector2f(centerSprite(spriteToCenter, referenceSprite.getGlobalBounds()));
	}



}