#pragma once
#ifndef SCENE_HPP_
#define SCENE_HPP_
#include "UI.hpp"
#include "Components.hpp"
#include <SFML/Graphics.hpp>

namespace SFGF {


	class Scene : public sf::Drawable {
	protected:

		bool isLeftMousePressed = false;
		bool isRightMousePressed = false;
		sf::Vector2f mousePos;

		typedef void(*sceneInit) ();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	public:
		std::vector<std::shared_ptr<sf::Drawable>> staticUI;
		std::vector<std::shared_ptr<UI>> ui;
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<ControlableObject>> controlableObjects;

		sf::Clock clock;

		[[maybe_unused]]
		sf::Music sceneTheme;

		sf::RenderWindow* owner;

		sceneInit initFunc;

		virtual void UpdateUI(sf::Event& event);
		virtual void Update(sf::Event& event);
		template<typename F>
		void SetInitFunc(F func) { this->initFunc = func; }
		virtual void SetActive(sf::RenderWindow& owner);
		virtual void DisableActive();

		


		Scene() = default;
		~Scene() = default;

		template<typename F>
		Scene(F func);

		Scene(Scene& scene);

		Scene& operator=(const Scene& scene);

		
	};

	class SceneManager : public sf::Drawable {
	private:
		Scene* activeScene;
	public:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void setActiveScene(Scene& scene, sf::RenderWindow& owner) {
			if (this->activeScene != nullptr)
				this->activeScene->DisableActive();
			this->activeScene = &scene;
			this->activeScene->SetActive(owner);
		}

		
		Scene* getActiveScene() { return this->activeScene; }
	};

	/*
	class Window : public sf::RenderWindow {
	private:
		sf::ContextSettings settings;

		sf::RenderWindow window;

		sf::Event event;

		Scene* activeScene;
	public:

		[[nodiscard]]
		bool isOpen() { return window.isOpen(); }

		void Show() { this->window.setActive(); }

		void Close() { this->window.close(); }

		[[likely]]
		void UpdateUI();

		[[nodiscard]]
		sf::Vector2f mapPixelToCoords(sf::Vector2i pixels);

		Window();
		~Window();
		Window(uint16_t width, uint16_t height);
		Window(uint16_t width, uint16_t height, Scene* scene);
		Window(uint16_t width, uint16_t height, Scene* scene, sf::ContextSettings settings);
		Window(uint16_t width, uint16_t height, Scene* scene, sf::ContextSettings settings, std::wstring title);

		Window(const Window& window);

		//[[nodiscard]]
		//sf::ContextSettings getSettings() { return this->settings; }

		[[nodiscard]]
		Scene* getActiveScene() { return this->activeScene; }

		[[nodiscard]]
		sf::RenderWindow& getRender() { return this->window; }
	};
	*/
}
#endif