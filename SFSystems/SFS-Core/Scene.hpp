#pragma once
#ifndef SCENE_HPP_
#define SCENE_HPP_
#include "Data.hpp"
#include "Base.hpp"
#include <SFML/Graphics.hpp>
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


		virtual void UpdateUI(sf::Event& event);
		virtual void Update(sf::Event& event);
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

	class SFS_C_API SceneManager : public sf::Drawable {
	private:
		sf::RenderWindow* owner;
		Scene* activeScene;
	public:
		SceneManager() = default;
		SceneManager(sf::RenderWindow* owner);
		

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void setActiveScene(Scene& scene) {
			if (this->activeScene != nullptr)
				this->activeScene->DisableActive();

			this->activeScene = &scene;
			this->activeScene->SetActive(this->owner);
		}

		void setOwner(sf::RenderWindow* owner) { if (owner != nullptr) this->owner = owner; }

		Scene* getActiveScene() { return this->activeScene; }
	};
}
#endif