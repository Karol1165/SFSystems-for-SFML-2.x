#pragma once
#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <ranges>
#include <functional>
#include <queue>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "framework.h"
#include "Task.hpp"
#include "Registrar.hpp"
#include "Builder.hpp"
#include "Overlay.hpp"


namespace SFS {
	class SceneManager;

	template <typename Derived>
	class BaseScene : public sf::Drawable {
	public:

		friend class SceneManager;

		using Task = BaseTask<Derived>;
		using TaskQueue = TaskQueue<Derived>;

		template <typename T>
		class Remove : public Task {
		private:
			std::string id;
			idVector<Registrar<T>>& container;
		public:
			Remove(const std::string& id, idVector<Registrar<T>>& container) : id(id), container(container) {}
			~Remove() = default;
			Remove& operator=(const Remove&) = default;
			Remove(const Remove&) = default;

			void doTask(Derived& scene) override {
				container.erase(id);
			}
		};

		BaseScene() = default;
		virtual ~BaseScene() = default;

		virtual void Update(sf::Event& event, const sf::Vector2f& mousePos) = 0;
		virtual void UpdateUI(sf::Event& event, const sf::Vector2f& mousePos) = 0;

		void setView(const sf::View& view) { this->SceneView = view; }

		[[nodiscard]]
		sf::View getView() const { return this->SceneView; }

		[[nodiscard]]
		sf::Time getDeltaTime() const { return this->clock.getElapsedTime(); }
		
	protected:

		bool isActive = false;

		sf::View SceneView;

		sf::Clock clock;

		TaskQueue tasks;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	};

	class SFS_S_API UIScene : public BaseScene<UIScene> {
	public:
		friend class SceneInitializer<UIScene>;

		virtual void UpdateUI(sf::Event& event, const sf::Vector2f& mousePos) override;
		virtual void Update(sf::Event& event, const sf::Vector2f& mousePos) override {}

		void addStaticUI(SceneElement* element) { this->staticUI.push_back(Registrar(element)); }

		void addStaticUI(const std::string& id, SceneElement* element) { this->staticUI.push_back(id, Registrar(element)); }

		void addUI(UI* element) { this->ui.push_back(Registrar(element)); }

		void addUI(const std::string& id, UI* element) { this->ui.push_back(id, Registrar(element)); }


		void removeStaticUI(const std::string& id) { this->tasks.addTask(new Remove<SceneElement>(id, staticUI)); }

		void removeUI(const std::string& id) { this->tasks.addTask(new Remove<UI>(id, ui)); }

		[[nodiscard]]
		const idVector<Registrar<SceneElement>>& getStaticUI() { return this->staticUI; }

		[[nodiscard]]
		const idVector<Registrar<UI>>& getUI() { return this->ui; }

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		idVector<Registrar<SceneElement>> staticUI;
		idVector<Registrar<UI>> ui;
	};
	
	class SFS_S_API Scene : public BaseScene<Scene> {
	private:

	public:
		friend class SceneInitializer<Scene>;

		virtual void UpdateUI(sf::Event& event, const sf::Vector2f& mousePos);
		virtual void Update(sf::Event& event, const sf::Vector2f& mousePos);

		Scene() = default;
		~Scene() = default;

		UIScene& getUIScene() { return this->GUI; }

		void addGameObject(GameObject* gameObject) { this->gameObjects.push_back(Registrar(gameObject)); }

		void addGameObject(const std::string& id, GameObject* gameObject) { this->gameObjects.push_back(id, Registrar(gameObject)); }

		void addController(BaseController* controller) { this->controllers.push_back(Registrar<BaseController>(controller)); }

		void addController(const std::string& id, BaseController* controller) { this->controllers.push_back(id, Registrar(controller)); }

		void removeGameObject(const std::string& id) { this->tasks.addTask(new Remove(id, gameObjects)); }

		void removeController(const std::string& id) { this->tasks.addTask(new Remove(id, controllers)); }

		[[nodiscard]]
		const idVector<Registrar<GameObject>>& getGameObjects() { return this->gameObjects; }

		[[nodiscard]]
		const idVector<Registrar<BaseController>>& getControllers() { return this->controllers; }

	protected:

		UIScene GUI;

		idVector<Registrar<GameObject>> gameObjects;
		idVector<Registrar<BaseController>> controllers;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};

	// TODO:  Naprawiæ sposób dodawania nowych scen do managera

	struct SceneEntry {
		enum class State { Unloaded, Loaded, Active };
		State state = State::Unloaded;
		Scene scene;
		sptr<SceneInitializer<Scene>> builder;
		~SceneEntry() {
			if (builder)
				builder->UnloadSceneResources();
		}
	};

	class SFS_S_API SceneManager {
	private:
		std::map<sf::String, SceneEntry> scenes;
		sf::String activeSceneID;
	public:
		SceneManager() = default;

		template <typename T>
			requires std::derived_from<T, SceneInitializer<Scene>>
		void addScene(const sf::String& id) {
			scenes.emplace(id, SceneEntry{ SceneEntry::State::Unloaded, Scene(), nullptr });
			scenes[id].builder = std::shared_ptr<T>(new T(&scenes[id].scene));
			if(scenes.size() == 1) {
				buildScene(id);
				scenes[id].builder->StartScene();
				scenes[id].state = SceneEntry::State::Active;
				activeSceneID = id;
			}
		}

		void changeScene(const sf::String& id);

		void buildScene(const sf::String& id);

		void unloadScene(const sf::String& id);

		[[nodiscard]]
		Scene& getCurrentScene() { return scenes[activeSceneID].scene; }
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
		using Init = InitFunc<Window>;
		using Task = BaseTask<Window>;
		using TaskQueue = TaskQueue<Window>;

		class ChangeScene : public Task {
		private:
			sf::String sceneID;
		public:
			ChangeScene(sf::String id) : sceneID(std::move(id)) {}
			void doTask(Window& window) override {
				window.sceneManager.changeScene(sceneID);
			}
		};



		friend class ChangeScene;

		Window();
		~Window() = default;

		Window(sf::VideoMode mode, const sf::String& title, uint32_t style = sf::Style::Default, const WindowSettings& settings = WindowSettings());
		Window(sf::WindowHandle handle, const WindowSettings& settings = WindowSettings());

		void create(sf::VideoMode mode, const sf::String& title, uint32_t style = sf::Style::Default, const WindowSettings& settings = WindowSettings());
		void create(sf::WindowHandle handle, const WindowSettings& settings);

		[[nodiscard]]
		sf::Color getClearColor() const { return this->clearColor; }

		void setClearColor(const sf::Color& color) { this->clearColor = color; }


		void changeWindowSettings(const WindowSettings& settings);

		void addTask(Task* newTask) { this->tasks.addTask(newTask); }

		void setScene(sf::String id) {
			this->addTask(new ChangeScene(std::move(id)));
		}

		template <typename T>
			requires std::derived_from<T, SceneInitializer<Scene>>
		void addScene(const sf::String& id) {
			sceneManager.addScene<T>(id);
		}

		[[nodiscard]]
		SceneManager& getSceneManager() { return this->sceneManager; }

		void setDebugOverlay(uptr<DebugOverlay> newOverlay) { this->debugOverlay = std::move(newOverlay); }

		/// Activates window, runs start function and main loop of program

		void run();
		
	private:
		SceneManager sceneManager = SceneManager();

		uptr<DebugOverlay> debugOverlay;

		bool isRunning = false;

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