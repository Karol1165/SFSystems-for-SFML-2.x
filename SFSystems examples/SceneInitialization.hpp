#pragma once
#ifndef SCENE_INITIALIZATION_HPP_
#define SCENE_INITIALIZATION_HPP_

#include <Data.hpp>
#include <UI.hpp>
#include <Scene.hpp>
#include "Res.hpp"
#include "Func.hpp"
#include <SFML/System.hpp>

using SFS::Registrar;
using SFS::Scene;
using SFS::SceneInitializer;



class MainSceneInitializer : public SceneInitializer<Scene> {
public:

	explicit MainSceneInitializer(Scene* target) : SceneInitializer<Scene>(target) {}
	// Executed before building this specific scene
	virtual void LoadSceneResources() {
		std::cout << "Main Scene Resources Loaded" << std::endl;
	}

	// Executed when the scene is being constructed
	virtual void BuildScene() override {
		sf::RectangleShape background = sf::RectangleShape();
		background.setPosition(0, 0);
		SFS::setRectangleData(titleBackgroundData, background);

		target->getUIScene().addStaticUI(new sf::RectangleShape(background));
		

		sf::Text text;
		SFS::setTextData(titleTextData, text);
		text.setString("SFSystems examples");
		text.setPosition(SFS::centerText(text, background));

		target->getUIScene().addStaticUI(new sf::Text(text));

		target->getUIScene().addUI(new SFS::TextButton(sf::Vector2f(200, 500), buttonBackgroundData, buttonSpottedBackgroundData,
			buttonTextData, buttonSpottedTextData, L"Options", optionsBtnFunc));
	}

	// Executed when the scene becomes active (enters update loop)
	virtual void StartScene() {
		std::cout << "Main Scene Started" << std::endl;
	}

	// Executed when the scene is being paused (exits update loop)
	virtual void PauseScene() {
		std::cout << "Main Scene Paused" << std::endl;
	}

	// Executed when the scene is being destroyed
	virtual void UnloadScene() {
		std::cout << "Main Scene Unloaded" << std::endl;
	}

	// Executed when the scene is being destroyed
	virtual void UnloadSceneResources() {
		std::cout << "Main Scene Resources Unloaded" << std::endl;
	}
};




class OptionsInitializer : public SceneInitializer<Scene> {
public:

	explicit OptionsInitializer(Scene* target) : SceneInitializer<Scene>(target) {}
	// Executed before building this specific scene
	virtual void LoadSceneResources() {
		std::cout << "Options Scene Resources Loaded" << std::endl;
	}

	// Executed when the scene is being constructed
	virtual void BuildScene() override {
		sf::RectangleShape background = sf::RectangleShape();
		background.setPosition(0, 0);
		SFS::setRectangleData(titleBackgroundData, background);

		target->getUIScene().addStaticUI(new sf::RectangleShape(background));
		

		sf::Text text;
		SFS::setTextData(titleTextData, text);
		text.setString("Options");
		text.setPosition(SFS::centerText(text, background));

		target->getUIScene().addStaticUI(new sf::Text(text));

		target->getUIScene().addUI(new SFS::TextButton(sf::Vector2f(440, 500), buttonBackgroundData, buttonSpottedBackgroundData,
			buttonTextData, buttonSpottedTextData, L"Back", menuBackBtnFunc));
	}

	// Executed when the scene becomes active (enters update loop)
	virtual void StartScene() {
		std::cout << "options Scene Started" << std::endl;
	}

	// Executed when the scene is being paused (exits update loop)
	virtual void PauseScene() {
		std::cout << "options Scene Paused" << std::endl;
	}

	// Executed when the scene is being destroyed
	virtual void UnloadScene() {
		std::cout << "options Scene Unloaded" << std::endl;
	}

	// Executed when the scene is being destroyed
	virtual void UnloadSceneResources() {
		std::cout << "options Scene Resources Unloaded" << std::endl;
	}
};

#endif