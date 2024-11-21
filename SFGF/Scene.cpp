#include "pch.h"
#include "Scene.hpp"

namespace SFGF {
	///Scene


	void Scene::UpdateUI(sf::Event& e) {
		
		mousePos = owner->mapPixelToCoords(sf::Mouse::getPosition(*owner));
		
		for (auto& i : std::ranges::reverse_view(ui)) {
			i->CheckStatus(e, clock.getElapsedTime(), mousePos);
		}

	}



	void Scene::Update(sf::Event& event) {
		for (auto& i : std::ranges::reverse_view(gameObjects)) {
			i->Update(event, clock.getElapsedTime(), mousePos);
		}
		for (auto& i : std::ranges::reverse_view(controllers)) {
			i->Update(event, clock.getElapsedTime(), mousePos);
		}
		clock.restart();
	}



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



	template<typename F>
	Scene::Scene(F func) {
		initFunc = func;
	}



	Scene::Scene(Scene& scene) {
		if(scene.initFunc != nullptr)
			this->initFunc = scene.initFunc;
		if(scene.owner != nullptr)
			this->owner = scene.owner;
	}


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


	void SceneManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*activeScene, states);
	}


}