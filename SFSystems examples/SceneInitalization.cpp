#include "SceneInitialization.hpp"

using namespace SFS;

void makeTitle(Scene& scene) {
	sf::RectangleShape background = sf::RectangleShape();
	background.setPosition(0, 0);
	SFS::setRectangleData(titleBackgroundData, background);


	scene.addStaticUI("titleBgr", new sf::RectangleShape(background));

	sf::Text text;
	SFS::setTextData(titleTextData, text);
	text.setString("SFSystems examples");
	text.setPosition(SFS::centerText(text, background));

	scene.addStaticUI(new sf::Text(text));
}

void mainSceneInitialization(Scene& scene) {
	makeTitle(scene);

	scene.addUI("OptionsBtn", new TextButton(sf::Vector2f(200, 500), buttonBackgroundData, buttonSpottedBackgroundData,
		buttonTextData, buttonSpottedTextData, L"Options", optionsBtnFunc));

}

void optionsSceneInitialization(Scene& scene) {
	makeTitle(scene);

	scene.addUI("BackBtn", new TextButton(sf::Vector2f(200, 500), buttonBackgroundData, buttonSpottedBackgroundData,
		buttonTextData, buttonSpottedTextData, L"Back", menuBackBtnFunc));
}