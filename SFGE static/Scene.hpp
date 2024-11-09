#pragma once
#ifndef SCENE_HPP_
#define SCENE_HPP_
#include "UI.hpp"
#include "Base.hpp"
#include <SFML/Graphics.hpp>

namespace SFGF {


	class Scene : public sf::Drawable {
	protected:

		bool isLeftMousePressed = false;
		bool isRightMousePressed = false;
		sf::Vector2f mousePos;



		typedef void(*sceneInit) (Scene&);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	public:
		std::vector<std::shared_ptr<sf::Drawable>> staticUI;
		std::vector<std::shared_ptr<UI>> ui;
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<BaseController>> controllers;


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

		[[nodiscard]]
		sf::Vector2f getMousePos() const {
			return this->mousePos;
		}

		[[nodiscard]]
		sf::Time getDeltaTime() const {
			return this->clock.getElapsedTime();
		}
		
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


}
#endif
