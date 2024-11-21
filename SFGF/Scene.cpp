#include "pch.h"
#include "Scene.hpp"

namespace SFGF {
	///Scene

	/// <summary>
	/// Shloud be put in while(Window.pollEvent(event)) loop
	/// </summary>
	/// <param name="e"></param>
	void Scene::UpdateUI(sf::Event& e) {
		
		mousePos = owner->mapPixelToCoords(sf::Mouse::getPosition(*owner));
		
		for (auto& i : std::ranges::reverse_view(ui)) {
			i->CheckStatus(e, clock.getElapsedTime(), mousePos);
		}

	}

	/// <summary>
	/// Shloud be put in main loop
	/// </summary>
	/// <param name="event"></param>

	void Scene::Update(sf::Event& event) {
		for (auto& i : std::ranges::reverse_view(gameObjects)) {
			i->Update(event, clock.getElapsedTime(), mousePos);
		}
		for (auto& i : std::ranges::reverse_view(controllers)) {
			i->Update(event, clock.getElapsedTime(), mousePos);
		}
		clock.restart();
	}


	/// <summary>
	/// Draw scene
	/// </summary>
	/// <param name="target"></param>
	/// <param name="states"></param>
	void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		for (auto& i : staticUI) {
			target.draw(*i, states);
		}
		for (auto& i : ui) {
			target.draw(*i, states);
		}
		for (auto& i : gameObjects) {
			target.draw(*i, states);
		}
	}


	/// <summary>
	/// Constructor that set scene initializing function
	/// </summary>
	/// <typeparam name="F"></typeparam>
	/// <param name="func"></param>
	template<typename F>
	Scene::Scene(F func) {
		initFunc = func;
	}


	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="scene"></param>
	Scene::Scene(Scene& scene) {
		if(scene.initFunc != nullptr)
			this->initFunc = scene.initFunc;
		if(scene.owner != nullptr)
			this->owner = scene.owner;
	}

	/// <summary>
	/// Starts playing scene music, and initialize scene.
	/// If scene is not actually used, do not call this method
	/// </summary>
	/// <param name="owner"></param>
	void Scene::SetActive(sf::RenderWindow& owner) {
		ui.clear();
		staticUI.clear();
		gameObjects.clear();

		if (initFunc != nullptr)
			initFunc(*this);

		this->owner = &owner;
		sceneTheme.play();
	}

	void Scene::DisableActive() {
		sceneTheme.pause();
	}

	Scene& Scene::operator=(const Scene& scene) {
		if(scene.initFunc != nullptr)
			this->initFunc = scene.initFunc;
		return *this;
	}


	//////////////////////////////////////////////
	/// SceneManager

	/// <summary>
	/// Draws actually active scene
	/// </summary>
	/// <param name="target"></param>
	/// <param name="states"></param>

	void SceneManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*activeScene, states);
	}


}