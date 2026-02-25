#pragma once
#ifndef SCENE_INITIALIZATION_HPP_
#define SCENE_INITIALIZATION_HPP_

#include <Data.hpp>
#include <UI.hpp>
#include <Scene.hpp>
#include <Builder.hpp>
#include "Res.hpp"
#include "Func.hpp"
#include "player.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using SFS::Registrar;
using SFS::Scene;
using SFS::SceneInitializer;

const float viewWidth = 1280;
const float viewHeight = 720;

void makeTitle(SFS::UIScene& target, const sf::String& string);
void setView(Scene& target);

class MainSceneInitializer : public SceneInitializer<Scene> {
public:
	explicit MainSceneInitializer(Scene* target) : SceneInitializer<Scene>(target) {}

	virtual void LoadSceneResources() {
		//std::cout << "Main Scene Resources Loaded" << std::endl;
	}

	virtual void BuildScene() override {
		makeTitle(target->getUIScene(), "SFSystems examples");
		setView(*target);

		target->getUIScene().addUI(new SFS::TextButton(sf::Vector2f(200, 200), buttonStyleData, L"Play example", playBtnFunc));
		target->getUIScene().addUI(new SFS::TextButton(sf::Vector2f(200, 300), buttonStyleData, L"Options", optionsBtnFunc));
		target->getUIScene().addUI(new SFS::TextButton(sf::Vector2f(200, 400), buttonStyleData, L"Exit", exitBtnFunc));

	}

	virtual void StartScene() {
		//std::cout << "Main Scene Started" << std::endl;
	}

	virtual void PauseScene() {
		//std::cout << "Main Scene Paused" << std::endl;
	}


	virtual void UnloadScene() {
		//std::cout << "Main Scene Unloaded" << std::endl;
	}


	virtual void UnloadSceneResources() {
		//std::cout << "Main Scene Resources Unloaded" << std::endl;
	}
};




class OptionsInitializer : public SceneInitializer<Scene> {
public:

	explicit OptionsInitializer(Scene* target) : SceneInitializer<Scene>(target) {}

	virtual void LoadSceneResources() {
		//std::cout << "Options Scene Resources Loaded" << std::endl;
	}


	virtual void BuildScene() override {
		makeTitle(target->getUIScene(), "Options");
		setView(*target);

		sf::Text languageLabel;
		SFS::setTextData(labelTextData, languageLabel);
		languageLabel.setString("Language:");
		languageLabel.setPosition(200, 200);

		target->getUIScene().addStaticUI(new sf::Text(languageLabel));



		//SFS::Switch languageSwitch(sf::Vector2f(400, 200), switchBgrData, switchTextData, buttonStyleData, L"English", L"Spanish", languageSwitchStates);

		target->getUIScene().addUI(new SFS::TextButton(sf::Vector2f(440, 500), buttonStyleData, L"Back", menuBackBtnFunc));
	}


	virtual void StartScene() {
		//std::cout << "options Scene Started" << std::endl;
	}


	virtual void PauseScene() {
		//std::cout << "options Scene Paused" << std::endl;
	}

	virtual void UnloadScene() {
		//std::cout << "options Scene Unloaded" << std::endl;
	}

	virtual void UnloadSceneResources() {
		//std::cout << "options Scene Resources Unloaded" << std::endl;
	}
};

class Example1Initializer : public SceneInitializer<Scene> {
private:
	circleShapeData* playerStyle = nullptr;
	circleShapeData* enemyStyle = nullptr;
public:
	explicit Example1Initializer(Scene* target) : SceneInitializer<Scene>(target) {}

	virtual void LoadSceneResources() {
		if (playerStyle == nullptr)
			playerStyle = new circleShapeData{ sf::Color::Green, sf::Color::Black, 50, 2 };
		if (enemyStyle == nullptr)
			enemyStyle = new circleShapeData{ sf::Color::Red, sf::Color::Black, 50, 2 };
	}

	virtual void BuildScene() override {
		makeTitle(target->getUIScene(), "Example 1");
		setView(*target);

		target->addGameObject("player", new Player(sf::Vector2f(100, 100), *playerStyle));

		target->addGameObject(new Enemy(sf::Vector2f(700, 100), *enemyStyle, target->getGameObjects()["player"].getAs<Player>()));

		target->addController(new Camera(&target->getView(), target->getGameObjects()["player"].getAs<Player>()));

		target->getUIScene().addUI(new SFS::TextButton(sf::Vector2f(440, 500), buttonStyleData, L"Back", menuBackBtnFunc));
	}

	virtual void StartScene() {
		//std::cout << "Example 1 Scene Started" << std::endl;
	}
	
	virtual void PauseScene() {
		//std::cout << "Example 1 Scene Paused" << std::endl;
	}

	virtual void UnloadScene() {
		//std::cout << "Example 1 Scene Unloaded" << std::endl;
	}

	virtual void UnloadSceneResources() {
		delete playerStyle, enemyStyle;
		playerStyle = nullptr;
		enemyStyle = nullptr;
		//std::cout << "Example 1 Scene Resources Unloaded" << std::endl;
	}
};

#endif