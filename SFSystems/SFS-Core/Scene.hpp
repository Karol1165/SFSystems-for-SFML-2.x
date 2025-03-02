#pragma once
#ifndef SCENE_HPP_
#define SCENE_HPP_
#include "Data.hpp"
#include "Base.hpp"
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<ranges>
#include "framework.h"

namespace SFS {

	//template <typename T>
	//using ptr = std::unique_ptr<T>;

	class SFS_C_API Scene : public sf::Drawable {
	protected:

		bool isLeftMousePressed = false;
		bool isRightMousePressed = false;
		sf::Vector2f mousePos;


		typedef void(*sceneInit) (Scene&);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		idVector<ptr<sf::Drawable>> staticUI;
		idVector<ptr<UI>> ui;
		idVector<ptr<GameObject>> gameObjects;
		idVector<ptr<BaseController>> controllers;


		sf::Clock clock;
		sf::Clock uiClock;

		[[maybe_unused]]
		sf::Music sceneTheme;

		sf::RenderWindow* owner;

		sceneInit initFunc;


		virtual void UpdateUI(sf::Event& event, const sf::Vector2f& mousePos);
		virtual void Update(sf::Event& event, const sf::Vector2f& mousePos);
		template<typename F>
		void SetInitFunc(F func) { this->initFunc = func; }
		virtual void SetActive(sf::RenderWindow* owner);
		virtual void SetActive();
		virtual void DisableActive();

		


		Scene() = default;
		~Scene() = default;

		template<typename F>
		Scene(F func);

		template <typename F>
		Scene(F initFunc, sf::RenderWindow* owner);

		Scene(const Scene& scene);

		Scene& operator=(const Scene& scene);

		[[nodiscard]]
		sf::Vector2f getMousePos() const {
			return this->mousePos;
		}

		[[nodiscard]]
		sf::Time getDeltaTime() const {
			return this->clock.getElapsedTime();
		}
		
	};

	class SFS_C_API SceneManager {
	private:
		sf::RenderWindow* owner;
		Scene* scene;
	public:
		SceneManager() : owner(nullptr), scene(nullptr) {}
		SceneManager(sf::RenderWindow* owner);
		


		void setScene(Scene& scene) {
			if (this->scene != nullptr)
				this->scene->DisableActive();
			this->scene = &scene;
		}
		void activateScene() {
			if (this->scene != nullptr)
				this->scene->SetActive(this->owner);
			else
				throw std::runtime_error("trying to activate not existing scene");
		}
		void changeScene(Scene& scene) {
			this->setScene(scene);
			this->activateScene();
		}


		void setOwner(sf::RenderWindow* owner) { if (owner != nullptr) this->owner = owner; }

		[[nodiscard]]
		bool hasOwner() const { return this->owner != nullptr; }

		[[nodiscard]]
		bool hasScene() const { return this->scene != nullptr; }

		Scene* getCurrentScene() { return this->scene; }
	};


	struct SFS_C_API WindowSettings {
		sf::ContextSettings contextSettings;
		bool vSyncEnabled;
		bool keyRepeatEnabled;
		uint16_t framerateLimit;
		WindowSettings(const sf::ContextSettings& contextSettings = sf::ContextSettings(), bool vSyncEnabled = false, bool keyRepeatEnabled = false,
			uint16_t framerateLimit = 30) {
			this->contextSettings = contextSettings;
			this->vSyncEnabled = vSyncEnabled;
			this->keyRepeatEnabled = keyRepeatEnabled;
			this->framerateLimit = framerateLimit;
		}
	};

	class SFS_C_API Window : public sf::RenderWindow {
	private:
		SceneManager manager;
		void initManager() noexcept;
		bool isWindowRunning = false;

		using windowInit = void(*) (Window&);
		windowInit initFunc;
	public:
		Window();
		~Window() = default;

		Window(sf::VideoMode mode, const sf::String& title, uint32_t style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
		Window(sf::WindowHandle handle, const sf::ContextSettings& settings = sf::ContextSettings());
		template <typename F>
		Window(F initFunc);

		void create(sf::VideoMode mode, const sf::String& title, uint32_t style = sf::Style::Default, const WindowSettings& settings = WindowSettings());
		void create(sf::WindowHandle handle, const WindowSettings& settings);

		template<typename F>
		void setInitFunc(F initFunc) {
			if (initFunc != nullptr)
				this->initFunc = initFunc;
		}

		void changeWindowSettings(const WindowSettings& settings);

		void setScene(Scene& scene) { this->manager.setScene(scene); }


		/// <summary>
		/// Activates window, runs start function and main loop of program
		/// </summary>
		void run();
		

	};
}
#endif