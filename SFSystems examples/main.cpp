#include<UI.hpp>
#include<Scene.hpp>
#include <Data.hpp>
#include "Res.hpp"
#include"SceneInitialization.hpp"
#include"Window.hpp"

int main() {
	initializeManagers();
	loadStaticResources();


	w.create(sf::VideoMode::getDesktopMode(), "Example");
	
	w.getSceneManager().addScene<MainSceneInitializer>(sf::String("MainMenu"));
	w.getSceneManager().addScene<OptionsInitializer>(sf::String("Options"));

	w.run();
	return 0;
}