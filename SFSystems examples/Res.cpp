#include"Res.hpp"

SFS::Window w;

sf::Font globalFont;

SFS::rectangleShapeData toolTipBackgroundData;
SFS::textData toolTipTextData;

SFS::rectangleShapeData titleBackgroundData;
SFS::rectangleShapeData buttonBackgroundData;
SFS::rectangleShapeData buttonSpottedBackgroundData;

SFS::textData titleTextData;
SFS::textData buttonTextData;
SFS::textData buttonSpottedTextData;

//SFS::LanguageResourcesManager languageManager;

void loadStaticResources() {
	globalFont.loadFromFile("C:/Windows/Fonts/Arial.ttf");

	titleBackgroundData.fillColor = sf::Color::Red;
	titleBackgroundData.outlineThickness = 0;
	titleBackgroundData.size = sf::Vector2f(350, 100);

	titleTextData.characterSize = 30;
	titleTextData.fillColor = sf::Color::Black;
	titleTextData.outlineThickness = 0;
	titleTextData.font = &globalFont;

	toolTipBackgroundData.fillColor = sf::Color::White;
	toolTipBackgroundData.outlineColor = sf::Color::Black;
	toolTipBackgroundData.outlineThickness = 1;
	toolTipBackgroundData.size = sf::Vector2f(100, 50);
	
	toolTipTextData.characterSize = 10;
	toolTipTextData.fillColor = sf::Color::Black;
	toolTipTextData.outlineThickness = 0;
	toolTipTextData.font = &globalFont;

	buttonBackgroundData.fillColor = sf::Color(50, 200, 200);
	buttonBackgroundData.outlineColor = sf::Color::Black;
	buttonBackgroundData.outlineThickness = 2;
	buttonBackgroundData.size = sf::Vector2f(200, 50);

	buttonSpottedBackgroundData.fillColor = sf::Color(50, 120, 120);
	buttonSpottedBackgroundData.outlineColor = sf::Color::Black;
	buttonSpottedBackgroundData.outlineThickness = 2;
	buttonSpottedBackgroundData.size = sf::Vector2f(250, 50);

	buttonTextData.characterSize = 20;
	buttonTextData.fillColor = sf::Color::Black;
	buttonTextData.outlineThickness = 0;
	buttonTextData.font = &globalFont;

	buttonSpottedTextData.characterSize = 18;
	buttonSpottedTextData.fillColor = sf::Color::Blue;
	buttonSpottedTextData.outlineThickness = 2;
	buttonSpottedTextData.outlineColor = sf::Color::Black;
	buttonSpottedTextData.font = &globalFont;
}

void initializeManagers() {
	//languageManager = SFS::LanguageResourcesManager("Resources", ".txt");
}