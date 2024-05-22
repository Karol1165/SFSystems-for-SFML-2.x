#pragma once
#ifndef WINDOW_HPP_
#define WINDOW_HPP_
#include "UI.hpp"
#include "Components.hpp"
#include <SFML/Graphics.hpp>

namespace SFGF {
	//Settings
	






	class Scene : public sf::Drawable {
	protected:
		typedef void(*sceneInit) ();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	public:
		std::vector<UI> ui;

		[[maybe_unused]]
		sf::Music sceneTheme;

		sf::RenderWindow* owner;

		sceneInit initFunc;

		virtual void Update(sf::Event& event);
		virtual void SetActive(sf::RenderWindow& owner);
		virtual void DisableActive();

		


		Scene();
		~Scene();

		template<typename F>
		Scene(F func);

		Scene(Scene& scene);
		
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
		void Update();

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