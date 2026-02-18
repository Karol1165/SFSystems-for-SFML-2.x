#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <Scene.hpp>
#include <Base.hpp>
#include <Data.hpp>

using namespace SFS;

class Character : public SFS::GameObject {
protected:
	sf::CircleShape shape;
	sf::Vector2f targetPos;
	float speed = 0.1f;
public:
	Character(sf::Vector2f pos, circleShapeData style) {
		setCircleData(style, shape);
		shape.setPosition(pos);
		shape.setOrigin(style.radius, style.radius);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(shape, states);
	}

	//TODO: make movement more complex, delete te relation between distacne and speed, add acceleration, etc
	void move() {
		shape.setPosition(shape.getPosition() + (targetPos - shape.getPosition()) * speed);
	}

	sf::Vector2f getPosition() const {
		return shape.getPosition();
	}
};

class Player : public Character {
public:
	Player(sf::Vector2f pos, circleShapeData style) : Character(pos, style) {}
	virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) override {
		
		move();
	}

};

class Enemy : public Character {
private:
	std::weak_ptr<Player> target;

public:
	Enemy(sf::Vector2f pos, circleShapeData style, std::weak_ptr<Player> target) : Character(pos, style) {
		this->target = target;
		this->speed = 0.05f;
	}

	virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) override {
		if(target.lock())
			targetPos = target.lock()->getPosition();
		move();
	}
};


#endif