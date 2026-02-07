#include"Res.hpp"

SFS::Window w;

sf::Font globalFont;

SFS::rectangleShapeData toolTipBackgroundData;
SFS::textData toolTipTextData;

SFS::rectangleShapeData titleBackgroundData;

SFS::textData titleTextData;

SFS::TextButton::StyleData buttonStyleData;

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

	buttonStyleData.mouseOutBgrData.fillColor = sf::Color(50, 200, 200);
	buttonStyleData.mouseOutBgrData.outlineColor = sf::Color::Black;
	buttonStyleData.mouseOutBgrData.outlineThickness = 2;
	buttonStyleData.mouseOutBgrData.size = sf::Vector2f(200, 50);

	buttonStyleData.mouseOnBgrData.fillColor = sf::Color(60, 150, 160);
	buttonStyleData.mouseOnBgrData.outlineColor = sf::Color::Black;
	buttonStyleData.mouseOnBgrData.outlineThickness = 2;
	buttonStyleData.mouseOnBgrData.size = sf::Vector2f(250, 50);

	buttonStyleData.mouseOutTextData.characterSize = 20;
	buttonStyleData.mouseOutTextData.fillColor = sf::Color::Black;
	buttonStyleData.mouseOutTextData.outlineThickness = 0;
	buttonStyleData.mouseOutTextData.font = &globalFont;

	buttonStyleData.mouseOnTextData.characterSize = 18;
	buttonStyleData.mouseOnTextData.fillColor = sf::Color::Blue;
	buttonStyleData.mouseOnTextData.outlineThickness = 2;
	buttonStyleData.mouseOnTextData.outlineColor = sf::Color::Black;
	buttonStyleData.mouseOnTextData.font = &globalFont;
}

void initializeManagers() {
	//languageManager = SFS::LanguageResourcesManager("Resources", ".txt");
}