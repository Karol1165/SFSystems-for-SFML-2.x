#pragma once
#ifndef UIVIEWS_HPP_
#define UIVIEWS_HPP_

#include "framework.h"


namespace SFS {

	////////////////////////////////////////////
	//Clipped View



	class ClippedView : public sf::Drawable {
	private:
		sf::FloatRect bounds;
		sf::Drawable* object;
		mutable sf::View view;

		void updateView() {
			this->view.setCenter(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
			this->view.setSize(bounds.width, bounds.height);
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		ClippedView() {
			this->object = nullptr;
			this->bounds = sf::FloatRect();
			this->view = sf::View();
		}
		~ClippedView() = default;

		ClippedView(const sf::FloatRect& bounds) {
			this->bounds = bounds;
			this->updateView();
			this->object = nullptr;
		}
		ClippedView(const sf::FloatRect& bounds, sf::Drawable* object) {
			this->bounds = bounds;
			this->updateView();
			this->object = object;
		}


		void setObject(sf::Drawable* newObject) {
			this->object = newObject;
		}
		void setBounds(const sf::FloatRect& newBounds) {
			this->bounds = newBounds;
			this->updateView();
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