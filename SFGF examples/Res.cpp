#include"Res.hpp"


SFS::SceneManager activeScene;

SFS::Scene mainScene;

sf::Font globalFont;


void loadStaticResources() {
	globalFont.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}