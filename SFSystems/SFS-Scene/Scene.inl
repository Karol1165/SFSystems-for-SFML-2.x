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

	template <typename Derived>
	template<typename T>
	void BaseScene<Derived>::addObject(idVector<ptr<T>>& container, T* newElement, std::vector<std::weak_ptr<Registrar<T>>> registrarContainer,
		std::optional<std::string> id) {
		if (!newElement)
			throw std::invalid_argument("Trying to add null element to scene");

		ptr<T> element = ptr<T>(newElement);

		if (id.has_value())
			container.push_back(id.value(), element);
		else
			container.push_back(element);

		if (registrarContainer.size() > 0) {
			for (auto& i : registrarContainer) {
				i.lock()->Register(element, &container, id);
			}
		}
	}

	template<typename Derived>
	template<typename T>
	void BaseScene<Derived>::addRegistrar(std::vector<std::weak_ptr<Registrar<T>>>& container, std::weak_ptr<Registrar<T>> newElement) {
		if (newElement.expired())
			throw std::invalid_argument("Trying to add expired registrar to scene");

		container.push_back(newElement);
	}

}