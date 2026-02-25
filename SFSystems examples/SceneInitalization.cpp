#include "SceneInitialization.hpp"

using namespace SFS;

void makeTitle(SFS::UIScene& target, const sf::String& string) {
	sf::RectangleShape background = sf::RectangleShape();
	background.setPosition(0, 0);
	SFS::setRectangleData(titleBackgroundData, background);

	target.addStaticUI(new sf::RectangleShape(background));


	sf::Text text;
	SFS::setTextData(titleTextData, text);
	text.setString(string);
	text.setPosition(SFS::centerText(text, background));
	SFS::ClippedView titleView = SFS::ClippedView(background.getGlobalBounds());
	titleView.setObject(new sf::Text(text));
	target.addStaticUI(new SFS::ClippedView(titleView));
}

void setView(Scene& target) {
	target.getView().setSize(sf::Vector2f(viewWidth, viewHeight));
	target.getView().setCenter(sf::Vector2f(viewWidth / 2, viewHeight / 2));
}