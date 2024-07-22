#pragma once
#ifndef BASE_HPP_
#define BASE_HPP_
#include <SFML/Graphics.hpp>

namespace SFGF {

	enum Direction {
		Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight
	};

	struct textData {
		int characterSize;
		sf::Color fillColor;
		sf::Color outlineColor;
		int outlineThickness;
	};
	inline void setTextData(const textData& data, sf::Text& object) {
		object.setCharacterSize(data.characterSize);
		object.setFillColor(data.fillColor);
		object.setOutlineColor(data.outlineColor);
		object.setOutlineThickness(data.outlineThickness);
	}
	struct rectangleShapeData {
		sf::Color fillColor;
		sf::Color outlineColor;
		sf::Vector2f size;
		int outlineThickness;
		sf::Texture texture;
	};
	inline void setRectangleData(const rectangleShapeData& data, sf::RectangleShape& object) {
		object.setSize(data.size);
		object.setFillColor(data.fillColor);
		object.setOutlineColor(data.outlineColor);
		object.setOutlineThickness(data.outlineThickness);
		object.setTexture(&data.texture);
	}
	struct circleShapeData {
		sf::Color fillColor;
		sf::Color outlineColor;
		int radius;
		int outlineThickness;
		sf::Texture texture;
	};
	inline void setCircleData(const circleShapeData& data, sf::CircleShape& object) {
		object.setRadius(data.radius);
		object.setFillColor(data.fillColor);
		object.setOutlineColor(data.outlineColor);
		object.setOutlineThickness(data.outlineThickness);
		object.setTexture(&data.texture);
	}

	/// <summary>
	/// Base class for all UI elements
	/// </summary>

	class UI : public sf::Drawable {
	public:
		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};




	class GameObject : public sf::Drawable {
	public:
		virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};

	class Controller {
    public:
	    virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) = 0;
	};




}
#endif