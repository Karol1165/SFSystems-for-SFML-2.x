#include "SceneInitialization.hpp"

void mainSceneInitialization(SFS::Scene& scene) {
	sf::RectangleShape background = sf::RectangleShape(sf::Vector2f(200, 100));
	background.setPosition(0, 0);
	background.setFillColor(sf::Color(255, 0, 0));

	scene.staticUI.push_back(SFS::ptr<sf::Drawable>(new sf::RectangleShape(background)));

	sf::Text text;
	text.setFont(globalFont);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color(255, 255, 255));
	text.setString("SFSystems examples");
	text.setPosition(SFS::centerText(text, background));



	scene.ui.push_back("titleToolTip", std::unique_ptr<SFS::UI>(new SFS::toolTip(toolTipBackgroundData, toolTipTextData, sf::Vector2f(20, 10),
		languageManager.getTranslation("titleToolTip", "EN"), globalFont,
		background.getGlobalBounds(), sf::seconds(2))));


	scene.staticUI.push_back(SFS::ptr<sf::Drawable>(new sf::Text(text)));
}