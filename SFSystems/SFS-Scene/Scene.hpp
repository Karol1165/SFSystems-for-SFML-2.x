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
#include "Task.hpp"
#include "Registrar.hpp"
#include "framework.h"

namespace SFS {

	class SceneInitializer;

	template <typename Derived>
	class BaseScene : public sf::Drawable {
	public:
		using InitFunc = void (*) (Derived&);
		using Task = BaseTask<Derived>;
		using TaskQueue = TaskQueue<Derived>;

		BaseScene() = default;
		~BaseScene() = default;
		BaseScene(const BaseScene&);
		BaseScene& operator=(const BaseScene&);

		virtual void SetActive();
		virtual void DisableActive() = 0;

		virtual void Update(sf::Event& event, const sf::Vector2f& mousePos) = 0;
		virtual void UpdateUI(sf::Event& event, const sf::Vector2f& mousePos) = 0;

		//To change
		void setInitFunc(InitFunc func) { this->initFunc = func; }

		void setView(const sf::View& view) { this->SceneView = view; }

		[[nodiscard]]
		bool getIsActive() const { return this->isActive; }

		[[nodiscard]]
		sf::View getView() const { return this->SceneView; }

		[[nodiscard]]
		sf::Time getDeltaTime() const { return this->clock.getElapsedTime(); }

		//To change
		[[nodiscard]]
		bool hasInitFunc() const { return this->initFunc; }
		
	protected:
		//To change
		InitFunc initFunc = nullptr;

		bool isActive = false;

		sf::View SceneView;

		sf::Clock clock;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	};

	class SFS_S_API UIScene : public BaseScene<UIScene> {
	public:

		virtual void UpdateUI(sf::Event& event, const sf::Vector2f& mousePos) override;
		virtual void Update(sf::Event& event, const sf::Vector2f& mousePos) override {}
		virtual void DisableActive() override;

		void addStaticUI(SceneElement* newElement, std::optional<std::string> id = std::nullopt);

		void addUI(UI* newElement, std::optional<std::string> id = std::nullopt);

	private:

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		idVector<Registrar<SceneElement>> staticUI;
		idVector<Registrar<UI>> ui;
	};
	
	class SFS_S_API Scene : public BaseScene<Scene> {
	public:

		virtual void UpdateUI(sf::Event& event, const sf::Vector2f& mousePos);
		virtual void Update(sf::Event& event, const sf::Vector2f& mousePos);
		virtual void SetActive() override;
		virtual void DisableActive() override;

		Scene() = default;
		~Scene() = default;
		//To change
		Scene(InitFunc func);


		void addGameObject(GameObject* newElement, std::optional<std::string> id = std::nullopt);

		void addController(BaseController* controller, std::optional<std::string> id = std::nullopt);
		
		UIScene& getUIScene() { return this->GUI; }

	private:



	protected:

		UIScene GUI;

		idVector<Registrar<GameObject>> gameObjects;
		idVector<Registrar<BaseController>> controllers;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
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
			if (this->scene)
				this->scene->DisableActive();
			this->scene = &scene;
		}

		void activateScene() {
			if (this->scene)
				this->scene->SetActive();
			else
				throw std::runtime_error("trying to activate not existing scene");
		}

		void changeScene(Scene& scene) {
			this->setScene(scene);
			this->activateScene();
		}


		void setOwner(sf::RenderWindow* owner) { if (owner) this->owner = owner; }

		[[nodiscard]]
		bool hasOwner() const { return this->owner; }

		[[nodiscard]]
		bool hasScene() const { return this->scene; }

		[[nodiscard]]
		Scene* getCurrentScene() const { return this->scene; }
	};



	/// All settings for window

	struct SFS_S_API WindowSettings {
		sf::ContextSettings contextSettings = sf::ContextSettings();
		bool vSyncEnabled = false;
		bool keyRepeatEnabled = false;
		uint16_t framerateLimit = 30;
	};

	class SFS_S_API Window : public sf::RenderWindow {
	public:
		using InitFunc = void(*) (Window&);
		using Task = BaseTask<Window>;
		using TaskQueue = TaskQueue<Window>;

		class ChangeScene : public Task {
		private:
			Scene* sceneToSet;
		public:
			ChangeScene(Scene* scene) : sceneToSet(scene) {}
			void doTask(Window& window) override {
				if (sceneToSet != nullptr)
					window.manager.changeScene(*sceneToSet);
			}
		};

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

		void setInitFunc(InitFunc initFunc) {
			if (initFunc != nullptr)
				this->initFunc = initFunc;
		}

		void changeWindowSettings(const WindowSettings& settings);

		void setScene(Scene& newScene) { this->tasks.addTask(new ChangeScene(&newScene)); }
		void addTask(Task* newTask) { this->tasks.addTask(newTask); }



		/// Activates window, runs start function and main loop of program

		void run();
		
	private:
		SceneManager manager;
		void initManager() noexcept;
		bool isWindowRunning = false;

		InitFunc initFunc;

		sf::Color clearColor = sf::Color::White;

		TaskQueue tasks;
		void doTasks() {
			this->tasks.executeAll(*this);
		}

		void changeNonContextSettings(const WindowSettings& settings) {
			this->setVerticalSyncEnabled(settings.vSyncEnabled);
			this->setKeyRepeatEnabled(settings.keyRepeatEnabled);
			this->setFramerateLimit(settings.framerateLimit);
		}
	};


}

#include "Scene.inl"

#endif