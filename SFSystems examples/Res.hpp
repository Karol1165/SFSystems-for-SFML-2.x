#pragma once
#ifndef RES_HPP_
#define RES_HPP_
#include<UI.hpp>
#include<Scene.hpp>
#include<Data.hpp>
#include<Resources.hpp>

extern SFS::Window window;

extern SFS::Scene mainScene;
extern SFS::Scene optionsScene;

extern sf::Font globalFont;

extern SFS::rectangleShapeData toolTipBackgroundData;
extern SFS::textData toolTipTextData;

extern SFS::rectangleShapeData titleBackgroundData;
extern SFS::rectangleShapeData buttonBackgroundData;
extern SFS::rectangleShapeData buttonSpottedBackgroundData;

extern SFS::textData titleTextData;
extern SFS::textData buttonTextData;
extern SFS::textData buttonSpottedTextData;

//extern SFS::LanguageResourcesManager languageManager;



void loadStaticResources();
void initializeManagers();


#endif