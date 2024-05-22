#include "pch.h"
#include "Window.hpp"

namespace SFGF {
	///Scene
	void Scene::Update(sf::Event& e) {
		bool isLeftMousePressed = false;
		bool isRightMousePressed = false;
		sf::Vector2f mousePos = owner->mapPixelToCoords(sf::Mouse::getPosition());
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				isLeftMousePressed = true;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			isRightMousePressed = true;
		}
		
		
		for (int i = 0; i < ui.size(); i++) {
			ui[i].CheckStatus(mousePos, isLeftMousePressed, isRightMousePressed);
		}
	}

	void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{
		for (int i = 0; i < this->ui.size(); i++) {
			target.draw(ui[i]);
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
		sceneInit();
		this->owner = &owner;
		sceneTheme.play();
	}

	void Scene::DisableActive() {
		sceneTheme.pause();
	}

	///Window


	/*
	sf::Vector2f Window::mapPixelToCoords(sf::Vector2i pixels) {
		return window.mapPixelToCoords(pixels);
	}

	void Window::Update() {
		this->window.pollEvent(this->event);
		this->activeScene->Update(this->event);
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