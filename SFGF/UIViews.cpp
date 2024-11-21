#include "pch.h"
#include "UIViews.hpp"

namespace SFGF {

	////////////////////////////////////////////////////////////////////
	//ClippedView

	template<DrawableType T>
	void ClippedView<T>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		sf::View view(bounds);
		renderTexture.setView(view);


		renderTexture.clear(sf::Color::Transparent);


		renderTexture.draw(*object, states);


		renderTexture.display();


		sf::Sprite sprite(renderTexture.getTexture());
		sprite.setPosition(bounds.left, bounds.top);


		target.draw(sprite, states);
	}



}