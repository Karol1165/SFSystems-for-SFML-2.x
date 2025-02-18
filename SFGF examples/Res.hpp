#pragma once
#ifndef RES_HPP_
#define RES_HPP_
#include<UI.hpp>
#include<Scene.hpp>
#include<Data.hpp>
#include<Resources.hpp>

extern SFS::SceneManager activeScene;

extern SFS::Scene mainScene;

extern sf::Font globalFont;

extern SFS::rectangleShapeData toolTipBackgroundData;
extern SFS::textData toolTipTextData;

extern SFS::LanguageResourcesManager languageManager;



void loadStaticResources();
void initializeManagers();


#endif