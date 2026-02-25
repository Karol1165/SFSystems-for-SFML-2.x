#pragma once
#ifndef RES_HPP_
#define RES_HPP_
#include<UI.hpp>
#include<Scene.hpp>
#include<Data.hpp>
#include<Resources.hpp>

extern 	SFS::Window w;

extern sf::Font globalFont;

extern const SFS::rectangleShapeData toolTipBackgroundData;
extern const SFS::textData toolTipTextData;

extern const SFS::rectangleShapeData titleBackgroundData;

extern const SFS::textData titleTextData;

extern const SFS::textData labelTextData;

extern const SFS::TextButton::StyleData buttonStyleData;

//extern SFS::LanguageResourcesManager languageManager;



void initializeManagers();
void loadFont();


#endif