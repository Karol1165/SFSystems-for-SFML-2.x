#include "pch.h"
#include "Controller.hpp"

namespace SFS {

	Controller::Controller(Scene& scene) {
		this->referenceScene = &scene;
	}

	FunctionController::FunctionController(Scene& scene, ControllerFunc func) : Controller(scene) {
		this->func = func;
	}

	void FunctionController::Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		this->func(*referenceScene);
	}

}