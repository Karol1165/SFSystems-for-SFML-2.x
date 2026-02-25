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
	sf::Vector2f velocity;
	float maxSpeed = 10.0f;
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
		if(velocity.x > maxSpeed)
			velocity.x = maxSpeed;
		else if(velocity.x < -maxSpeed)
			velocity.x = -maxSpeed;
		if (velocity.y > maxSpeed)
			velocity.y = maxSpeed;
		else if (velocity.y < -maxSpeed)
			velocity.y = -maxSpeed;

		shape.setPosition(shape.getPosition().x + velocity.x, shape.getPosition().y + velocity.y);
	}

	sf::Vector2f getPosition() const {
		return shape.getPosition();
	}
};

class Player : public Character {
private:
	
public:
	Player(sf::Vector2f pos, circleShapeData style) : Character(pos, style) {}
	virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) override {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			velocity.y -= 5.f * deltaTime.asSeconds();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			velocity.y += 5.f * deltaTime.asSeconds();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			velocity.x -= 5.f * deltaTime.asSeconds();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			velocity.x += 5.f * deltaTime.asSeconds();
		}
		
		move();
	}

};

class Enemy : public Character {
private:
	std::weak_ptr<Player> target;
	sf::Vector2f targetPos;
public:
	Enemy(sf::Vector2f pos, circleShapeData style, std::weak_ptr<Player> target) : Character(pos, style) {
		this->target = target;
		maxSpeed = 5.0f;
	}

	virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) override {
		if (target.lock()) 
			targetPos = target.lock()->getPosition();
		if(targetPos.x > shape.getPosition().x)
			velocity.x += 5.f * deltaTime.asSeconds();
		else if(targetPos.x < shape.getPosition().x)
			velocity.x -= 5.f * deltaTime.asSeconds();
		if (targetPos.y > shape.getPosition().y)
			velocity.y += 5.f * deltaTime.asSeconds();
		else if (targetPos.y < shape.getPosition().y)
			velocity.y -= 5.f * deltaTime.asSeconds();
		
		move();
	}
};

class Camera : public SFS::BaseController {
private:
	std::weak_ptr<Player> target;
	sf::View* view;

public:
	Camera(sf::View* view, std::weak_ptr<Player> target) {
		this->view = view;
		this->target = target;
	}
	virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) override {
		if (target.lock()) {
			view->setCenter(target.lock()->getPosition());
		}
	}
};


#endif