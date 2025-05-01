#pragma once
#ifndef REGISTRAR_HPP_
#define REGISTRAR_HPP_
#include<optional>
#include <string>
#include <vector>
#include "Base.hpp"
#include "Data.hpp"
#include "framework.h"

namespace SFS {

	template<typename T>
	class Registrar {
	public:
		virtual void Register(ptr<T> elementToRegister, idVector<ptr<T>>* container, std::optional<std::string> id) {
			if (!elementToRegister.get() || (void*)elementToRegister.get() == (void*)this)
				return;
			if(!this->container)
				this->container = container;
			SaveElement(elementToRegister, id);
		}
	protected:
		virtual void SaveElement(ptr<T> elementToRegister, std::optional<std::string> id) = 0;

		idVector<ptr<T>>* container = nullptr;
	};

}
#endif