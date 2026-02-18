#pragma once
#ifndef BASE_HPP_
#define BASE_HPP_

#include <SFML/Graphics.hpp>

#include "framework.h"



namespace SFS {

	using SceneElement = sf::Drawable;

	template <typename T>
	using InitFunc = void(*) (T&);

	template <typename B, typename D>
	concept DerivedFrom = std::derived_from<D, B>;

	template <template <typename> typename Base, typename D>
	concept CRTP = std::is_base_of_v<Base<D>, D>;


	// Interface class for all UI elements

	class SFS_C_API UI : public SceneElement {
	public:
		UI() = default;
		virtual ~UI() = default;

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};


	// Interface class for game objects
		
	class SFS_C_API GameObject : public SceneElement {
	public:
		GameObject() = default;
		virtual ~GameObject() = default;

		virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};


	// Interface class for controllers

	class SFS_C_API BaseController {
	public:
		BaseController() = default;
		virtual ~BaseController() = default;

	    virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) = 0;
	};

}
#endif