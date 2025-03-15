#pragma once
#ifndef TOOLTIP_HPP_
#define TOOLTIP_HPP_

#include "framework.h"
#include "Base.hpp"
#include "Data.hpp"
#include "Math.hpp"
#include "UIViews.hpp"
#include <optional>

namespace SFS {
	////////////////////////////////////////
	//toolTip

	class SFS_UI_API toolTip : public UI {
	private:
		sf::RectangleShape background;
		sf::Text text;
		ClippedView textView;
		sf::FloatRect fieldWhenActive;
		bool isVisible = false;

		std::optional<sf::Time> cursorOverTime;
		std::optional<sf::Time> requiredCursorOverTime;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:

		toolTip() = default;
		~toolTip() = default;
		toolTip(rectangleShapeData backgroundData, textData tipTextData, sf::Vector2f pos, std::wstring text, sf::Font& textFont, sf::FloatRect fieldWhenVisible,
			sf::Time timeToActivate = sf::Time::Zero);

		virtual void CheckStatus(sf::Event& e, const sf::Time& deltaTime = sf::Time(sf::seconds(0)), const sf::Vector2f& mousePos = sf::Vector2f(0, 0)) override;
	};
}

#endif