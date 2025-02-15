#pragma once
#ifndef UIVIEWS_HPP_
#define UIVIEWS_HPP_
#include "Base.hpp"
#include "Data.hpp"
#include "framework.h"

namespace SFS {

	////////////////////////////////////////////
	//Clipped View

	template <typename T>
	concept DrawableType = std::is_base_of_v<sf::Drawable, T>;

	template <DrawableType T>

	class ClippedView : public sf::Drawable {
	private:
		mutable sf::RenderTexture renderTexture;
		sf::FloatRect bounds;
		T* object;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
			sf::View view(bounds);
			renderTexture.setView(view);


			renderTexture.clear(sf::Color::Transparent);


			renderTexture.draw(*object, states);


			renderTexture.display();


			sf::Sprite sprite(renderTexture.getTexture());
			sprite.setPosition(bounds.left, bounds.top);


			target.draw(sprite, states);
		}
	public:
		ClippedView() = default;
		~ClippedView() = default;

		ClippedView(sf::FloatRect bounds) {
			this->bounds = bounds;
			renderTexture.create(static_cast<unsigned int>(bounds.width), static_cast<unsigned int>(bounds.height));
		}


		void setObject(const T* newObject) {
			this->object = const_cast<T*>(newObject);
		}
		void setBounds(sf::FloatRect newBounds) {
			this->bounds = newBounds;
			renderTexture.create(static_cast<unsigned int>(bounds.width), static_cast<unsigned int>(bounds.height));
		}


	};

	////////////////////////////////////////////
	//ScroolView

	/// <summary>
	/// Class of ScroolView
	/// </summary>

	/*
	* TODO:
	class SFS_UI_API ScroolView : public UI {
	private:
		std::vector<ptr<UI>> elements;

		sf::RectangleShape scroolBackground;
		sf::CircleShape scroolCircle;
	public:
		ScroolView() = default;
		~ScroolView() = default;

		void AddElement(ptr<UI> newElement);

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;
	};
	*/
}

#endif