#include "pch.h"
#include "UIViews.hpp"

namespace SFS {

	////////////////////////////////////////////////////////////////////
	//ClippedView

	void ClippedView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (!object)
			return;

		this->view.setViewport(sf::FloatRect(
			bounds.left / target.getSize().x,
			bounds.top / target.getSize().y,
			bounds.width / target.getSize().x,
			bounds.height / target.getSize().y
		));

		sf::View oldView = target.getView();

		target.setView(view);

		target.draw(*object, states);

		target.setView(oldView);
	}



}