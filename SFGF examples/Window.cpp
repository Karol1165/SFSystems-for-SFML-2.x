#include"Window.hpp"
#include "Res.hpp"
#include "SceneInitialization.hpp"

void MainWindowInitFunc(SFS::Window& w) {
	initializeManagers();
	loadStaticResources();
	mainScene.SetInitFunc(mainSceneInitialization);
	optionsScene.SetInitFunc(optionsSceneInitialization);

	w.create(sf::VideoMode(1500, 800), "Example");
	w.setScene(mainScene);

	
}