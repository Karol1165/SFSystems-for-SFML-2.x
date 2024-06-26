#pragma once
#ifndef BASE_HPP_
#define BASE_HPP_
#include <SFML/Graphics.hpp>

namespace SFGF {

	struct textData {
		int characterSize;
		sf::Color fillColor;
		sf::Color outlineColor;
		int outlineThickness;
	};
	struct rectangleShapeData {
		sf::Color fillColor;
		sf::Color outlineColor;
		sf::Vector2f size;
		int outlineThickness;
		sf::Texture texture;
	};
	struct circleShapeData {
		sf::Color fillColor;
		sf::Color outlineColor;
		int radius;
		int outlineThickness;
		sf::Texture texture;
	};

	/// <summary>
	/// Base class for all UI elements
	/// </summary>

	class UI : public sf::Drawable {
	public:
		virtual void CheckStatus(const sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};


	class GameObject : public sf::Drawable {
	public:
		virtual void Update() = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};

	class ControlableObject : public GameObject {
	public:
		virtual void Update(const sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};




}
#endif