#pragma once
#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_
#include <SFML/Graphics.hpp>

namespace SFGF {

	//add if object is doing something when it is clicked
	class Clickable {
	protected:
		//Checking click and doing something
		virtual bool CheckClick(sf::Vector2f mousePos, bool isClicked);
	};

	//add if object can collision with other objects
	class Collisionable {
	protected:
		//Checking collision and doing something
		virtual void CheckCollision(Collisionable object);
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