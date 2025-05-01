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

		this->staticUIRegistrars.clear();
		this->UIRegistrars.clear();
	}

	void UIScene::addStaticUI(SceneElement* newElement) {
		this->addObject(this->staticUI, newElement, this->staticUIRegistrars, std::nullopt);
	}

	void UIScene::addStaticUI(std::string id, SceneElement* newElement) {
		this->addObject(this->staticUI, newElement, this->staticUIRegistrars, id);
	}

	void UIScene::addStaticUIRegistrar(std::weak_ptr<Registrar<SceneElement>> registrar) {
		this->addRegistrar(this->staticUIRegistrars, registrar);
	}

	void UIScene::addUI(UI* newElement) {
		this->addObject(this->ui, newElement, this->UIRegistrars, std::nullopt);
	}

	void UIScene::addUI(std::string id, UI* newElement) {
		this->addObject(this->ui, newElement, this->UIRegistrars, id);
	}

	void UIScene::addUIRegistrar(std::weak_ptr<Registrar<UI>> registrar) {
		this->addRegistrar(this->UIRegistrars, registrar);
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

	Scene::Scene(InitFunc func) {
		this->setInitFunc(func);
	}

	void Scene::SetActive() {
		BaseScene<Scene>::SetActive();

		this->GUI.SetActive();
	}

	void Scene::DisableActive() {
		this->GUI.DisableActive();

		this->gameObjects.clear();
		this->controllers.clear();

		this->gameObjectRegistrars.clear();
		this->controllerRegistrars.clear();
	}

	void Scene::addStaticUI(SceneElement* newElement) {
		this->GUI.addStaticUI(newElement);
	}

	void Scene::addStaticUI(std::string id, SceneElement* newElement) {
		this->GUI.addStaticUI(id, newElement);
	}

	void Scene::addStaticUIRegistrar(std::weak_ptr<Registrar<SceneElement>> registrar) {
		this->GUI.addStaticUIRegistrar(registrar);
	}

	void Scene::addUI(UI* newElement) {
		this->GUI.addUI(newElement);
	}

	void Scene::addUI(std::string id, UI* newElement) {
		this->GUI.addUI(id, newElement);
	}

	void Scene::addUIRegistrar(std::weak_ptr<Registrar<UI>> registrar) {
		this->GUI.addUIRegistrar(registrar);
	}

	void Scene::addGameObject(GameObject* newElement) {
		this->addObject(this->gameObjects, newElement, this->gameObjectRegistrars, std::nullopt);
	}

	void Scene::addGameObject(std::string id, GameObject* newElement) {
		this->addObject(this->gameObjects, newElement, this->gameObjectRegistrars, id);
	}

	void Scene::addGameObjectRegistrar(std::weak_ptr<Registrar<GameObject>> registrar) {
		this->addRegistrar(this->gameObjectRegistrars, registrar);
	}

	void Scene::addController(BaseController* controller) {
		this->addObject(this->controllers, controller, this->controllerRegistrars, std::nullopt);
	}

	void Scene::addController(std::string id, BaseController* controller) {
		this->addObject(this->controllers, controller, this->controllerRegistrars, id);
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
		//Checking if settings that need recreation of the window are the same
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