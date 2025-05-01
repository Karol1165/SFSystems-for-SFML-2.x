#include"Window.hpp"
#include "Res.hpp"
#include "SceneInitialization.hpp"

void MainWindowInitFunc(SFS::Window& w) {
	initializeManagers();
	loadStaticResources();
	mainScene.setInitFunc(mainSceneInitialization);
	optionsScene.setInitFunc(optionsSceneInitialization);

	w.create(sf::VideoMode(1500, 800), "Example");
	w.setScene(mainScene);

	
}