#include<UI.hpp>
#include<Scene.hpp>
#include <Data.hpp>
#include "Res.hpp"
#include"SceneInitialization.hpp"

//TODO: make example scene, something that shows how to use game objects and controllers

int main() {
	initializeManagers();
	loadStaticResources();


	w.create(sf::VideoMode(1280, 720), "Example");
	
	w.getSceneManager().addScene<MainSceneInitializer>(sf::String("MainMenu"));
	w.getSceneManager().addScene<OptionsInitializer>(sf::String("Options"));
	w.getSceneManager().addScene<Example1Initializer>(sf::String("Example 1"));

	w.run();
	return 0;
}