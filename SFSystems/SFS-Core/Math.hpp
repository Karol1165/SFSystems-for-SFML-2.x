#pragma once
#ifndef MATH_H_
#define MATH_H_
#include<SFML/Graphics.hpp>
#include <numbers>
#include "framework.h"

constexpr double pi = std::numbers::pi;
constexpr double radiansToDegrees = 180.0 / pi;

namespace SFS {

	/// <summary>
	/// Function to calculate angle that is between two points
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>angle in degrees, where 0 means up</returns>
	[[nodiscard]]
	SFS_C_API double Angle_Between_Points(sf::Vector2f a, sf::Vector2f b);


	/// <summary>
	/// simple function to center 2 bounds
	/// </summary>
	/// <param name="boundsToCenter"></param>
	/// <param name="background"></param>
	/// <returns>centered position of 1st bounds</returns>
	[[nodiscard]]
	SFS_C_API sf::Vector2f center(const sf::FloatRect& boundsToCenter, const sf::FloatRect& background);

	/// <summary>
	/// specialized function to center text on a sprite
	/// </summary>
	/// <param name="text"></param>
	/// <param name="button"></param>
	/// <returns>centered position for text</returns>
	[[nodiscard]]
	SFS_C_API sf::Vector2f centerText(const sf::Text& text, const sf::Sprite& button);

	/// <summary>
	/// specialized function to center text on a Rectangle
	/// </summary>
	/// <param name="text"></param>
	/// <param name="shape"></param>
	/// <returns>centered position of text</returns>
	[[nodiscard]]
	SFS_C_API sf::Vector2f centerText(const sf::Text& text, const sf::RectangleShape& shape);

	/// <summary>
	/// specialized function to center text on bounds
	/// </summary>
	/// <param name="text"></param>
	/// <param name="bounds"></param>
	/// <returns>centered position of text</returns>
	[[nodiscard]]
	SFS_C_API sf::Vector2f centerText(const sf::Text& text, const sf::FloatRect& bounds);


	/// <summary>
	/// specialized function to center sprite on other sprite
	/// </summary>
	/// <param name="spriteToCenter"></param>
	/// <param name="referenceSprite"></param>
	/// <returns>Centered position of first sprite</returns>
	 
	[[nodiscard]]
	SFS_C_API sf::Vector2f centerSprite(const sf::Sprite& spriteToCenter, const sf::Sprite& referenceSprite);

	/// <summary>
	/// specialized function to center sprite on bounds
	/// </summary>
	/// <param name="spriteToCenter"></param>
	/// <param name="bounds"></param>
	/// <returns>centered position of sprite</returns>
	[[nodiscard]]
	SFS_C_API sf::Vector2f centerSprite(const sf::Sprite& spriteToCenter, const sf::FloatRect& bounds);

	/// <summary>
	/// specialized function to center sprite on rectangle
	/// </summary>
	/// <param name="spriteToCenter"></param>
	/// <param name="background"></param>
	/// <returns>centered position of sprite</returns>
	[[nodiscard]]
	SFS_C_API sf::Vector2f centerSprite(const sf::Sprite& spriteToCenter, const sf::RectangleShape& background);

}

#endif


