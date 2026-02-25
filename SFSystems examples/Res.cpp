#include"Res.hpp"

SFS::Window w;

sf::Font globalFont;

const SFS::rectangleShapeData toolTipBackgroundData = SFS::rectangleShapeData{ sf::Color::White, sf::Color::Black, sf::Vector2f(100, 50), 1 };
const SFS::textData toolTipTextData = SFS::textData{ 10, sf::Color::Black, sf::Color(), 0, &globalFont };

const SFS::rectangleShapeData titleBackgroundData = SFS::rectangleShapeData{ sf::Color::Red, sf::Color::Transparent,  sf::Vector2f(300, 100), 0 };

const SFS::textData titleTextData = SFS::textData{ 30, sf::Color::Black, sf::Color::Transparent, 0, &globalFont };

const SFS::textData labelTextData = SFS::textData{ 25, sf::Color::Black, sf::Color(), 0, &globalFont};

const SFS::TextButton::StyleData buttonStyleData = SFS::TextButton::StyleData{
		SFS::rectangleShapeData(sf::Color(60, 150, 160), sf::Color::Black, sf::Vector2f(250, 60), 2),
		SFS::rectangleShapeData(sf::Color(50, 200, 200), sf::Color::Black, sf::Vector2f(200, 60), 2),
		SFS::soundData(nullptr, 100, 1, false),
		SFS::soundData(nullptr, 100, 1, false),
		SFS::textData(24, sf::Color::Blue, sf::Color::Black, 2, &globalFont),
		SFS::textData(24, sf::Color::Black, sf::Color::Transparent, 0, &globalFont)
};

//SFS::LanguageResourcesManager languageManager;

void loadFont() {
	globalFont.loadFromFile("C:/Windows/Fonts/arial.ttf");
}

void initializeManagers() {
	//languageManager = SFS::LanguageResourcesManager("Resources", ".txt");
}