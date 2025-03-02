#include"Window.hpp"
#include "Res.hpp"
#include "SceneInitialization.hpp"

void MainWindowInitFunc(SFS::Window& w) {
	initializeManagers();
	loadStaticResources();
	mainScene.SetInitFunc(mainSceneInitialization);

	w.create(sf::VideoMode(1200, 800), "Example");
	mainScene.SetInitFunc(mainSceneInitialization);
	w.setScene(mainScene);

	
}