#include<UI.hpp>
#include<Scene.hpp>
#include <Data.hpp>
#include "Res.hpp"
#include"SceneInitialization.hpp"

//TODO: make example scene, something that shows how to use game objects and controllers

int main() {
	initializeManagers();
	loadFont();


	w.create(sf::VideoMode(1280, 720), "Example");
	
	w.addScene<MainSceneInitializer>(sf::String("MainMenu"));
	w.addScene<OptionsInitializer>(sf::String("Options"));
	w.addScene<Example1Initializer>(sf::String("Example 1"));

	w.run();
	return 0;
}