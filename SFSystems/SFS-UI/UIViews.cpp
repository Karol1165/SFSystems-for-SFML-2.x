#include "pch.h"
#include "UIViews.hpp"

namespace SFS {

	////////////////////////////////////////////////////////////////////
	//ClippedView

	void ClippedView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if (!object)
			return;

		sf::View oldView = target.getView();



		this->view.setViewport(sf::FloatRect(
			bounds.left / target.getSize().x * (target.getSize().x / oldView.getSize().x ),
			bounds.top / target.getSize().y * (target.getSize().y / oldView.getSize().y),
			bounds.width / target.getSize().x * (target.getSize().x / oldView.getSize().x),
			bounds.height / target.getSize().y * (target.getSize().y / oldView.getSize().y)
		));



		target.setView(view);

		target.draw(*object, states);

		target.setView(oldView);
	}



}