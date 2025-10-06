#include "pch.h"
#include "Scene.hpp"

namespace SFS {

	template <typename Derived>
	BaseScene<Derived>::BaseScene(const BaseScene& scene) : initFunc(scene.initFunc) {}

	template <typename Derived>
	BaseScene<Derived>& BaseScene<Derived>::operator=(const BaseScene& scene) {
		this->initFunc = scene.initFunc;
		return *this;
	}

	template <typename Derived>
	void BaseScene<Derived>::SetActive() {
		if (this->initFunc)
			this->initFunc(*static_cast<Derived*>(this));
#ifdef _DEBUG
		else
			std::cerr << "Scene has no init function" << std::endl;
#endif // _DEBUG
		this->isActive = true;
	}





}