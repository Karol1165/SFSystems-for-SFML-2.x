#include "pch.h"
#include "Scene.hpp"

namespace SFS {
	///Scene

	void Scene::UpdateUI(sf::Event& event, const sf::Vector2f& mousePos) {
		for (auto& i : std::ranges::reverse_view(ui)) {
			i->CheckStatus(event, this->uiClock.getElapsedTime(), mousePos);
		}
		this->uiClock.restart();
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
		for (auto& i : this->staticUI) {
			target.draw(*i, states);
		}
		for (auto& i : this->ui) {
			target.draw(*i, states);
		}
		for (auto& i : this->gameObjects) {
			target.draw(*i, states);
		}
	}



	template<typename F>
	Scene::Scene(F func) {
		if(func)
			this->initFunc = func;
		else 
			this->initFunc = nullptr;
	}

	template <typename F>
	Scene::Scene(F initFunc, sf::RenderWindow* owner) : Scene(initFunc) {
		if (owner)
			this->owner = owner;
	}

	Scene::Scene(const Scene& scene) : Scene(scene.initFunc) {
		if(scene.owner)
			this->owner = scene.owner;
	}

	void Scene::SetActive() {
		if (this->owner) {
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
		if (owner)
			this->owner = owner;
		else
			this->owner = nullptr;
		this->SetActive();
	}

	void Scene::DisableActive() {
		sceneTheme.pause();
	}

	Scene& Scene::operator=(const Scene& scene) {
		if (scene.initFunc)
			this->initFunc = scene.initFunc;
		if (scene.owner)
			this->owner = scene.owner;
		return *this;
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

	Window::Window(sf::VideoMode mode, const sf::String& title, uint32_t style, const sf::ContextSettings& settings) 
		: sf::RenderWindow(mode, title, style, settings) {
		this->initManager();
	}

	Window::Window(sf::WindowHandle handle, const sf::ContextSettings& settings)
		: sf::RenderWindow(handle, settings) {
		this->initManager();
	}

	template <typename F>
	Window::Window(F initFunc) {
		this->setInitFunc(initFunc);
	}

	void Window::create(sf::VideoMode mode, const sf::String& title, uint32_t style, const WindowSettings& settings) {
		sf::RenderWindow::create(mode, title, style, settings.contextSettings);
		this->setVerticalSyncEnabled(settings.vSyncEnabled);
		this->setKeyRepeatEnabled(settings.keyRepeatEnabled);
		this->setFramerateLimit(settings.framerateLimit);
	}

	void Window::create(sf::WindowHandle handle, const WindowSettings& settings) {
		sf::RenderWindow::create(handle, settings.contextSettings);
		this->setVerticalSyncEnabled(settings.vSyncEnabled);
		this->setKeyRepeatEnabled(settings.keyRepeatEnabled);
		this->setFramerateLimit(settings.framerateLimit);
	}



	void Window::changeWindowSettings(const WindowSettings& settings) {
		if (this->getSettings().antialiasingLevel == settings.contextSettings.antialiasingLevel &&
			this->getSettings().attributeFlags == settings.contextSettings.attributeFlags &&
			this->getSettings().depthBits == settings.contextSettings.depthBits &&
			this->getSettings().majorVersion == settings.contextSettings.majorVersion &&
			this->getSettings().minorVersion == settings.contextSettings.minorVersion &&
			this->getSettings().sRgbCapable == settings.contextSettings.sRgbCapable &&
			this->getSettings().stencilBits == settings.contextSettings.stencilBits) {
			this->setFramerateLimit(settings.framerateLimit);
			this->setVerticalSyncEnabled(settings.vSyncEnabled);
			this->setKeyRepeatEnabled(settings.keyRepeatEnabled);
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
			if (this->initFunc != nullptr)
				this->initFunc(*this);

			this->manager.activateScene();


			sf::Event e;
			sf::Vector2f mousePos;
			bool hasEvents;

			sf::Event fakeEvent;
			fakeEvent.type = sf::Event::Count;

			while (this->isOpen()) {

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

				this->clear();

				this->draw(*manager.getCurrentScene());

				this->display();
			}
		}
		catch (std::exception exeption) {
			this->close();
		}
		this->isWindowRunning = false;
	}
	
}