#include"Res.hpp"


SFS::SceneManager activeScene;

SFS::Scene mainScene;

sf::Font globalFont;

SFS::rectangleShapeData toolTipBackgroundData;
SFS::textData toolTipTextData;

SFS::LanguageResourcesManager languageManager;

void loadStaticResources() {
	globalFont.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	toolTipBackgroundData.fillColor = sf::Color(255, 255, 255);
	toolTipBackgroundData.outlineColor = sf::Color(0, 0, 0);
	toolTipBackgroundData.outlineThickness = 1;
	toolTipBackgroundData.size = sf::Vector2f(100, 50);
	
	toolTipTextData.characterSize = 10;
	toolTipTextData.fillColor = sf::Color(0, 0, 0);
	toolTipTextData.outlineThickness = 0;
}

void initializeManagers() {
	languageManager = SFS::LanguageResourcesManager("Resources", ".txt");
}