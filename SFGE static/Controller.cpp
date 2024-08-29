#include "pch.h"
#include "Controller.hpp"

namespace SFGF {

	FunctionController::FunctionController(Scene& scene, ControllerFunc func) : Controller(scene) {
		this->func = func;
	}

	void FunctionController::Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) {
		this->func(referenceScene);
	}

}