#pragma once
#ifndef SCENE_HPP_
#define SCENE_HPP_
#include "Data.hpp"
#include "Base.hpp"
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<ranges>
#include <functional>
#include <queue>
#include "framework.h"

namespace SFS {

	//template <typename T>
	//using ptr = std::unique_ptr<T>;



	class SFS_S_API Scene : public sf::Drawable {
	protected:

		bool isLeftMousePressed = false;
		bool isRightMousePressed = false;
		sf::Vector2f mousePos;

		sf::View SceneView;

		sf::Clock clock;
		sf::Clock uiClock;

		typedef void(*sceneInit) (Scene&);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	public:
		idVector<ptr<sf::Drawable>> staticUI;
		idVector<ptr<UI>> ui;
		idVector<ptr<GameObject>> gameObjects;
		idVector<ptr<BaseController>> controllers;




		[[maybe_unused]]
		sf::Music sceneTheme;

		sf::RenderWindow* owner;

		sceneInit initFunc;


		virtual void UpdateUI(sf::Event& event, const sf::Vector2f& mousePos);
		virtual void Update(sf::Event& event, const sf::Vector2f& mousePos);
		template<typename F>
		void SetInitFunc(F func) { this->initFunc = func; }
		virtual void SetActive(sf::RenderWindow* owner);
		virtual void DisableActive();

		


		Scene() : owner(nullptr), initFunc(nullptr) {}
		~Scene() = default;

		template<typename F>
		Scene(F func);



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
		[[nodiscard]]
		sf::RenderWindow* getOwner() const {
			return this->owner;
		}
		
	};

	class SFS_S_API SceneManager {
	private:
		sf::RenderWindow* owner;
		Scene* scene;
	public:
		SceneManager() {
			this->owner = nullptr;
			this->scene = nullptr;
		}
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


	/// <summary>
	/// All settings for window
	/// </summary>
	struct SFS_S_API WindowSettings {
		sf::ContextSettings contextSettings = sf::ContextSettings();
		bool vSyncEnabled = false;
		bool keyRepeatEnabled = false;
		uint16_t framerateLimit = 30;
	};

	class SFS_S_API Window : public sf::RenderWindow {
	private:
		SceneManager manager;
		void initManager() noexcept;
		bool isWindowRunning = false;

		using windowInit = void(*) (Window&);
		windowInit initFunc;

		sf::Color clearColor = sf::Color::White;

		struct WindowTask {
			virtual void doTask(Window& window) = 0;
		};
		struct ChangeScene : WindowTask {
			Scene* sceneToSet;
			ChangeScene(Scene* scene) : sceneToSet(scene) {}
			void doTask(Window& window) override {
				if (sceneToSet != nullptr) 
					window.manager.changeScene(*sceneToSet);
				
			}
		};
		std::queue<std::unique_ptr<WindowTask>> tasks;
		void doTasks() {
			while (!this->tasks.empty()) {
				this->tasks.front()->doTask(*this);
				this->tasks.pop();
			}
		}

		void changeNonContextSettings(const WindowSettings& settings) {
			this->setVerticalSyncEnabled(settings.vSyncEnabled);
			this->setKeyRepeatEnabled(settings.keyRepeatEnabled);
			this->setFramerateLimit(settings.framerateLimit);
		}
		
	public:
		Window();
		~Window() = default;

		Window(sf::VideoMode mode, const sf::String& title, uint32_t style = sf::Style::Default, const WindowSettings& settings = WindowSettings());
		Window(sf::WindowHandle handle, const WindowSettings& settings = WindowSettings());
		template <typename F>
		Window(F initFunc) {
			this->setInitFunc(initFunc);
			this->initManager();
		}

		void create(sf::VideoMode mode, const sf::String& title, uint32_t style = sf::Style::Default, const WindowSettings& settings = WindowSettings());
		void create(sf::WindowHandle handle, const WindowSettings& settings);

		[[nodiscard]]
		sf::Color getClearColor() const { return this->clearColor; }

		void setClearColor(const sf::Color& color) { this->clearColor = color; }

		template<typename F>
		void setInitFunc(F initFunc) {
			if (initFunc != nullptr)
				this->initFunc = initFunc;
		}

		void changeWindowSettings(const WindowSettings& settings);

		void setScene(Scene& scene) { 
			this->tasks.push(std::unique_ptr<WindowTask>(new ChangeScene(&scene)));
		}


		/// <summary>
		/// Activates window, runs start function and main loop of program
		/// </summary>
		void run();
		

	};
}
#endif