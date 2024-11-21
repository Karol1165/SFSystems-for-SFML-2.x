#pragma once
#ifndef UIVIEWS_HPP_
#define UIVIEWS_HPP_
#include "Base.hpp"

namespace SFGF {

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
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
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

	class ScroolView : public UI {
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

}

#endif