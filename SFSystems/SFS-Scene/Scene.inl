#include "Scene.hpp"

namespace SFS {

	template <typename Derived>
	BaseScene<Derived>::BaseScene(const BaseScene& scene) : initializer(scene.initializer) {}

	template <typename Derived>
	BaseScene<Derived>& BaseScene<Derived>::operator=(const BaseScene& scene) {
		this->initializer = scene.initializer;
		return *this;
	}

	template <typename Derived>
	void BaseScene<Derived>::SetActive() {
		if (this->initializer)
			this->initializer->InitializeScene();
#ifdef _DEBUG
		else
			std::cerr << "Scene has no initializer" << std::endl;
#endif
		this->isActive = true;
	}





}