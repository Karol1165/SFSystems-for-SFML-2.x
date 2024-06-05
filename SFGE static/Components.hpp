#pragma once
#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_
#include <SFML/Graphics.hpp>

namespace SFGF {

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


	//add if object is doing something when it is clicked
	class Clickable {
	protected:
		//Checking click and doing something
		virtual bool CheckClick(sf::Vector2f mousePos, bool isClicked) = 0;
	};

	//add if object can collision with other objects
	class Collisionable {
	protected:
		//Checking collision and doing something
		virtual void CheckCollision(Collisionable object) = 0;
	};

	//add if object has HP and can be destroyed
	class Destroyable {
	protected:
		//Health Points
		int HP;
		virtual void Destroy() { delete this; }
	public:
		Destroyable(int hp) : HP(hp) {}

		virtual void AddDamage(int value) { HP -= value; if (HP < 0) Destroy(); }
		virtual void AddHP(int value) { HP += value; }
	};

}
#endif