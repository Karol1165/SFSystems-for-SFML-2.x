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

	void UIScene::DisableActive() {
		this->ui.clear();
		this->staticUI.clear();
	}





	///Scene

	void Scene::UpdateUI(sf::Event& event, const sf::Vector2f& mousePos) {
		this->GUI.UpdateUI(event, mousePos);
	}

	void Scene::Update(sf::Event& event, const sf::Vector2f& mousePos) {
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

	void Scene::SetActive() {
		BaseScene<Scene>::SetActive();

		this->GUI.SetActive();
	}

	void Scene::DisableActive() {
		this->GUI.DisableActive();

		this->gameObjects.clear();
		this->controllers.clear();
	}



	//////////////////////////////////////////////
	/// SceneManager

	SceneManager::SceneManager(sf::RenderWindow* owner) {
		this->setOwner(owner);
		this->scene = nullptr;
	}



	void Window::initManager() noexcept {
		if(!this->manager.hasOwner())
			this->manager = SceneManager(this);
	}

	Window::Window() : sf::RenderWindow() {
		this->initManager();
	}

	Window::Window(sf::VideoMode mode, const sf::String& title, uint32_t style, const WindowSettings& settings) 
		: sf::RenderWindow(mode, title, style, settings.contextSettings) {
		this->changeNonContextSettings(settings);
		this->initManager();
	}

	Window::Window(sf::WindowHandle handle, const WindowSettings& settings)
		: sf::RenderWindow(handle, settings.contextSettings) {
		this->changeNonContextSettings(settings);
		this->initManager();
	}



	void Window::create(sf::VideoMode mode, const sf::String& title, uint32_t style, const WindowSettings& settings) {
		sf::RenderWindow::create(mode, title, style, settings.contextSettings);
		this->changeNonContextSettings(settings);
		this->initManager();
	}

	void Window::create(sf::WindowHandle handle, const WindowSettings& settings) {
		sf::RenderWindow::create(handle, settings.contextSettings);
		this->changeNonContextSettings(settings);
		this->initManager();
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
		if (this->isWindowRunning)
			return;
		this->isWindowRunning = true;
		try {
			if (this->initFunc)
				this->initFunc(*this);

			this->doTasks();

			sf::Event e;
			sf::Vector2f mousePos;
			bool hasEvents;

			sf::Event fakeEvent;
			fakeEvent.type = sf::Event::Count;

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
					manager.getCurrentScene()->UpdateUI(e, mousePos);
				}
				if (!hasEvents) {
					manager.getCurrentScene()->UpdateUI(fakeEvent, mousePos);
				}
				manager.getCurrentScene()->Update(e, mousePos);

				this->clear(this->clearColor);

				this->draw(*manager.getCurrentScene());

				this->display();
			}
		}
		catch (const std::exception) {
			this->close();
		}
		this->isWindowRunning = false;
	}
	
}