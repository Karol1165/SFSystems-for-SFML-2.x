#include "pch.h"
#include "Scene.hpp"

namespace SFS {
	///Scene


	void Scene::UpdateUI(sf::Event& event) {
		
		mousePos = owner->mapPixelToCoords(sf::Mouse::getPosition(*owner));
		
		for (auto& i : std::ranges::reverse_view(ui)) {
			i->CheckStatus(event, this->uiClock.getElapsedTime(), mousePos);
		}
		this->uiClock.restart();
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
		if(func != nullptr)
			initFunc = func;
	}

	template <typename F>
	Scene::Scene(F initFunc, sf::RenderWindow* owner) : Scene(initFunc) {
		if (owner != nullptr)
			this->owner = owner;
	}

	Scene::Scene(const Scene& scene) {
		if(scene.initFunc != nullptr)
			this->initFunc = scene.initFunc;
		if(scene.owner != nullptr)
			this->owner = scene.owner;
	}

	void Scene::SetActive() {
		if (this->owner != nullptr) {
			this->ui.clear();
			this->staticUI.clear();
			this->gameObjects.clear();
			this->controllers.clear();

			if (this->initFunc != nullptr)
				this->initFunc(*this);
			else
				throw std::runtime_error("Trying to activate scene without initialization");

			this->sceneTheme.play();
		}
		else
			throw std::runtime_error("Trying to activate scene without owner window");
	}

	void Scene::SetActive(sf::RenderWindow* owner) {
		this->owner = owner;
		this->SetActive();
	}

	void Scene::DisableActive() {
		sceneTheme.pause();
	}

	Scene& Scene::operator=(const Scene& scene) {
		if (scene.initFunc != nullptr)
			this->initFunc = scene.initFunc;
		if (scene.owner != nullptr)
			this->owner = scene.owner;
		return *this;
	}


	//////////////////////////////////////////////
	/// SceneManager

	SceneManager::SceneManager(sf::RenderWindow* owner) {
		if (owner != nullptr)
			this->owner = owner;
	}

	void SceneManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*activeScene, states);
	}


}