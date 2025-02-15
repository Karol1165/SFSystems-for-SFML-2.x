#pragma once
#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_
#include "Scene.hpp"
#include "framework.h"

namespace SFS {

	class SFS_C_API Controller : public BaseController {
	protected:

		Scene& referenceScene;

	public:
		Controller(Scene& scene) : referenceScene(scene) {}
		Controller() = delete;
		~Controller() = default;

		virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) = 0;
	};

	class SFS_C_API FunctionController : public Controller {
	private:
		typedef void (*ControllerFunc) (Scene&);
		ControllerFunc func;
	public:
		FunctionController(Scene& scene, ControllerFunc func);
		~FunctionController() = default;

		virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) override;
	};


}

#endif