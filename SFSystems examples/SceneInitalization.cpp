#include "SceneInitialization.hpp"

using namespace SFS;

void makeTitle(Scene& scene) {
	sf::RectangleShape background = sf::RectangleShape();
	background.setPosition(0, 0);
	SFS::setRectangleData(titleBackgroundData, background);


	scene.getUIScene().addStaticUI(new sf::RectangleShape(background), "titleBgr");

	sf::Text text;
	SFS::setTextData(titleTextData, text);
	text.setString("SFSystems examples");
	text.setPosition(SFS::centerText(text, background));

	scene.getUIScene().addStaticUI(new sf::Text(text));
}

void mainSceneInitialization(Scene& scene) {
	makeTitle(scene);

	scene.getUIScene().addUI( new TextButton(sf::Vector2f(200, 500), buttonBackgroundData, buttonSpottedBackgroundData,
		buttonTextData, buttonSpottedTextData, L"Options", optionsBtnFunc), "OptionsBtn");

}

void optionsSceneInitialization(Scene& scene) {
	makeTitle(scene);

	scene.getUIScene().addUI(new TextButton(sf::Vector2f(200, 500), buttonBackgroundData, buttonSpottedBackgroundData,
		buttonTextData, buttonSpottedTextData, L"Back", menuBackBtnFunc), "BackBtn");
}