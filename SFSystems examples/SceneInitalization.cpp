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

	target.addStaticUI(new sf::Text(text));
}