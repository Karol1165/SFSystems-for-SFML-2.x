#include "pch.h"
#include "Window.hpp"

namespace SFGF {
	///Scene

	/// <summary>
	/// Shloud be putted in while(Window.pollEvent(event)) loop
	/// </summary>
	/// <param name="e"></param>
	void Scene::UpdateUI(sf::Event& e) {
		
		mousePos = owner->mapPixelToCoords(sf::Mouse::getPosition(*owner));
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				isLeftMousePressed = true;
		}
		else
		{
			isLeftMousePressed = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			isRightMousePressed = true;
		}
		else {
			isRightMousePressed = false;
		}
		
		
		for (auto& i : ui) {
			i->CheckStatus(e, clock.getElapsedTime(), mousePos);
		}

		for (auto& i : gameObjects) {
			i->Update();
		}


	}

	/// <summary>
	/// Shloud be putted in main loop
	/// </summary>
	/// <param name="event"></param>

	void Scene::Update(sf::Event& event) {
		for (auto& i : controlableObjects) {
			i->Update(event, clock.getElapsedTime(), mousePos);
		}
		clock.restart();
	}

	void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		for (auto& i : ui) {
			target.draw(*i);
		}
		for (auto& i : staticUI) {
			target.draw(*i);
		}
	}

	template<typename F>
	Scene::Scene(F func) {
		initFunc = func;
	}

	Scene::Scene(Scene& scene) {
		this->initFunc = scene.initFunc;
		this->owner = scene.owner;
	}


	void Scene::SetActive(sf::RenderWindow& owner) {
		ui.clear();
		staticUI.clear();
		gameObjects.clear();
		controlableObjects.clear();
		if (initFunc != nullptr)
			initFunc();
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

	///Window


	/*
	sf::Vector2f Window::mapPixelToCoords(sf::Vector2i pixels) {
		return window.mapPixelToCoords(pixels);
	}

	void Window::UpdateUI() {
		this->window.pollEvent(this->event);
		this->activeScene->UpdateUI(this->event);
		window.clear();
		window.draw(*activeScene);
		window.display();
	}

	Window::Window() {
		this->settings = sf::ContextSettings();
		this->window.create(sf::VideoMode(100, 100) , "" , 7U , settings );
	}
	Window::~Window() {
		this->window.close();
	}
	Window::Window(uint16_t width, uint16_t height) {
		this->settings = sf::ContextSettings();
		this->window.create(sf::VideoMode(width, height), "", 7U, settings);
	}
	Window::Window(uint16_t width, uint16_t height, Scene* scene) {
		this->settings = sf::ContextSettings();
		this->window.create(sf::VideoMode(width, height), "", 7U, settings);
		this->activeScene->DisableActive();
		this->activeScene = scene;
		this->activeScene->SetActive(this);
	}
	Window::Window(uint16_t width, uint16_t height, Scene* scene, sf::ContextSettings settings) {
		this->settings = settings;
		this->window.create(sf::VideoMode(width, height), "", 7U, settings);
		this->activeScene->DisableActive();
		this->activeScene = scene;
		this->activeScene->SetActive(this);
	}
	Window::Window(uint16_t width, uint16_t height, Scene* scene, sf::ContextSettings settings, std::wstring title) {
		this->settings = settings;
		this->window.create(sf::VideoMode(width, height), title, 7U, settings);
		this->activeScene->DisableActive();
		this->activeScene = scene;
		this->activeScene->SetActive(this);
	}
	Window::Window(const Window& window) {
		this->settings = window.settings;
		this->create(window.getSystemHandle(), window.getSettings());
		this->activeScene = window.activeScene;
	}
	*/
}