#pragma once
#ifndef MATH_H_
#define MATH_H_
#include<SFML/Graphics.hpp>
#include "definitions.h"


namespace SFGF {

	[[nodiscard]]
	double Angle_Between_Points(sf::Vector2f a, sf::Vector2f b);

	[[nodiscard]]
	sf::Vector2f centerText(const sf::Text& text, const sf::Sprite& button);

	[[nodiscard]]
	sf::Vector2f centerText(const sf::Text& text, const sf::RectangleShape& shape);


	/// <summary>
	/// Returns position of sprite, where this sprite is on center of other sprite
	/// </summary>
	/// <param name="spriteToCenter"></param>
	/// <param name="referenceSprite"></param>
	/// <returns>Centered position of sprite</returns>
	 
	[[nodiscard]]
	sf::Vector2f centerSprite(sf::Sprite& spriteToCenter, sf::Sprite& referenceSprite);

}

#endif // !MATH_H_


