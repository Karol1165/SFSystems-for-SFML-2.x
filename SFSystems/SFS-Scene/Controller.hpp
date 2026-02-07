#pragma once
#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include "framework.h"
#include "Scene.hpp"

namespace SFS {

	class SFS_S_API Controller : public BaseController {
	protected:

		Scene* referenceScene;

	public:
		Controller(Scene& scene);
		Controller() = delete;
		~Controller() = default;

		Controller(const Controller&) = delete;
		Controller operator=(const Controller&) = delete;

		virtual void Update(sf::Event& e, const sf::Time& deltaTime, const sf::Vector2f& mousePos) = 0;
	};

	class SFS_S_API FunctionController : public Controller {
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