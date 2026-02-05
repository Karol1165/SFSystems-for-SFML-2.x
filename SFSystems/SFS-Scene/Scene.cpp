#include "pch.h"
#include "Scene.hpp"

namespace SFS {

	void UIScene::UpdateUI(sf::Event& event, const sf::Vector2f& mousePos) {
		for (auto& i : std::ranges::reverse_view(ui)) {
			i->CheckStatus(event, this->clock.getElapsedTime(), mousePos);
		}
		this->clock.restart();
	}

	void UIScene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (auto& i : this->staticUI) {
			target.draw(*i, states);
		}
		for (auto& i : this->ui) {
			target.draw(*i, states);
		}
	}



	///Scene

	void Scene::UpdateUI(sf::Event& event, const sf::Vector2f& mousePos) {
		this->GUI.UpdateUI(event, mousePos);
	}

	void Scene::Update(sf::Event& event, const sf::Vector2f& mousePos) {
		tasks.executeAll(*this);
		for (auto& i : std::ranges::reverse_view(gameObjects)) {
			i->Update(event, clock.getElapsedTime(), mousePos);
		}
		for (auto& i : std::ranges::reverse_view(controllers)) {
			i->Update(event, clock.getElapsedTime(), mousePos);
		}
		clock.restart();
	}

	void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		for (auto& i : this->gameObjects) {
			target.draw(*i, states);
		}
		target.draw(this->GUI, states);
	}



	//////////////////////////////////////////////
	/// SceneManager

	void SceneManager::changeScene(const sf::String& id) {
		if (activeSceneID == id)
			return;

		if(scenes.find(id) == scenes.end())
			throw std::runtime_error("Scene with ID '" + id.toAnsiString() + "' does not exist in SceneManager.");


		scenes[activeSceneID].builder->PauseScene();
		scenes[activeSceneID].state = SceneEntry::State::Loaded;

		if(scenes[id].state == SceneEntry::State::Unloaded)
			buildScene(id);

		scenes[id].builder->StartScene();
		scenes[id].state = SceneEntry::State::Active;

		activeSceneID = id;
	}

	void SceneManager::buildScene(const sf::String& id) {
		auto& entry = scenes[id];
		if (entry.state == SceneEntry::State::Active)
			return;

		if(entry.state == SceneEntry::State::Unloaded)
			entry.builder->LoadSceneResources();
	
		entry.builder->BuildScene();
	}

	void SceneManager::unloadScene(const sf::String& id) {
		auto& entry = scenes[id];
		if (entry.state == SceneEntry::State::Unloaded)
			return;
		entry.builder->UnloadScene();
		entry.builder->UnloadSceneResources();
		entry.state = SceneEntry::State::Unloaded;
	}

	Window::Window() : sf::RenderWindow() {
	}

	Window::Window(sf::VideoMode mode, const sf::String& title, uint32_t style, const WindowSettings& settings) 
		: sf::RenderWindow(mode, title, style, settings.contextSettings) {
		this->changeNonContextSettings(settings);
	}

	Window::Window(sf::WindowHandle handle, const WindowSettings& settings)
		: sf::RenderWindow(handle, settings.contextSettings) {
		this->changeNonContextSettings(settings);
	}



	void Window::create(sf::VideoMode mode, const sf::String& title, uint32_t style, const WindowSettings& settings) {
		sf::RenderWindow::create(mode, title, style, settings.contextSettings);
		this->changeNonContextSettings(settings);

	}

	void Window::create(sf::WindowHandle handle, const WindowSettings& settings) {
		sf::RenderWindow::create(handle, settings.contextSettings);
		this->changeNonContextSettings(settings);

	}



	void Window::changeWindowSettings(const WindowSettings& settings) {
		//Check if context-related settings have changed (requires full window recreation)
		if (this->getSettings().antialiasingLevel == settings.contextSettings.antialiasingLevel &&
			this->getSettings().attributeFlags == settings.contextSettings.attributeFlags &&
			this->getSettings().depthBits == settings.contextSettings.depthBits &&
			this->getSettings().majorVersion == settings.contextSettings.majorVersion &&
			this->getSettings().minorVersion == settings.contextSettings.minorVersion &&
			this->getSettings().sRgbCapable == settings.contextSettings.sRgbCapable &&
			this->getSettings().stencilBits == settings.contextSettings.stencilBits) {
			this->changeNonContextSettings(settings);
		}
		else {
			this->create(this->getSystemHandle(), settings);
		}
	}



	void Window::run() {
		if (this->isRunning)
			return;
		this->isRunning = true;
		try {

			this->doTasks();

			sf::Event e;
			sf::Vector2f mousePos;
			bool hasEvents;
			sf::Event heartBeatEvent = technicalEvent();

			while (this->isOpen()) {

				this->doTasks();

				mousePos = this->mapPixelToCoords(sf::Mouse::getPosition(*this), this->getView());
				hasEvents = false;
				while (this->pollEvent(e)) {
					hasEvents = true;
					if (e.type == sf::Event::Closed) {
						this->close();
						break;
					}
					sceneManager.getCurrentScene().UpdateUI(e, mousePos);
				}
				if (!hasEvents) {
					sceneManager.getCurrentScene().UpdateUI(heartBeatEvent, mousePos);
				}
				sceneManager.getCurrentScene().Update(e, mousePos);

				this->clear(this->clearColor);

				this->draw(sceneManager.getCurrentScene());

				this->display();
			}
		}
		catch (const std::exception) {
			this->close();
		}
		this->isRunning = false;
	}
	
}