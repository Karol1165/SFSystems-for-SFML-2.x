#include "SceneInitialization.hpp"

void makeTitle(SFS::Scene& scene) {
	sf::RectangleShape background = sf::RectangleShape();
	background.setPosition(0, 0);
	SFS::setRectangleData(titleBackgroundData, background);


	scene.staticUI.push_back("titleBgr", SFS::ptr<sf::Drawable>(new sf::RectangleShape(background)));

	sf::Text text;
	SFS::setTextData(titleTextData, text);
	text.setString("SFSystems examples");
	text.setPosition(SFS::centerText(text, background));

	scene.staticUI.push_back(SFS::ptr<sf::Drawable>(new sf::Text(text)));
}

void mainSceneInitialization(SFS::Scene& scene) {
	makeTitle(scene);

	scene.ui.push_back("OptionsBtn", SFS::ptr<SFS::UI>(new SFS::TextButton(sf::Vector2f(200, 500), buttonBackgroundData, buttonSpottedBackgroundData, 1, globalFont,
		buttonTextData, buttonSpottedTextData, L"Options", optionsBtnFunc)));



}

void optionsSceneInitialization(SFS::Scene& scene) {
	makeTitle(scene);
}