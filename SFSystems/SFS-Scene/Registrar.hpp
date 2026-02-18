#pragma once
#ifndef REGISTRAR_HPP_
#define REGISTRAR_HPP_

#include<optional>
#include <string>
#include <vector>
#include <concepts>
#include<typeindex>
#include <memory>

#include "framework.h"

namespace SFS {

	//Template class to store and manage objects

	template<typename T>
	class Registrar {
	public:
		Registrar() = delete;

		~Registrar() = default;

		explicit Registrar(sptr<T> object) : object(object) {}

		
		explicit Registrar(T* object) {
			this->object = std::shared_ptr<T>(object);
		}

		[[nodiscard]]
		std::weak_ptr<T> getAsBase() const { return std::weak_ptr<T>(object); }

		template <typename D> requires DerivedFrom<T, D>
		[[nodiscard]]
		std::weak_ptr<D> getAs() const {
			if (auto casted = std::dynamic_pointer_cast<D>(object)) [[likely]]
				return std::weak_ptr<D>(casted);
			else [[unlikely]]
				return std::weak_ptr<D>();
		}

		[[nodiscard]]
		T* operator->() const { return object.get(); }

		[[nodiscard]]
		T& operator*() const { return *object; }

	private:
		sptr<T> object;
	};

}
#endif