#pragma once
#ifndef REGISTRAR_HPP_
#define REGISTRAR_HPP_
#include<optional>
#include <string>
#include <vector>
#include <concepts>
#include<typeindex>
#include <memory>
#include "Base.hpp"
#include "Data.hpp"
#include "framework.h"

namespace SFS {
	template <typename T, typename U>
	concept DerivedFrom = std::derived_from<U, T>;


	//Template class to store and manage objects

	template<typename T>
	class Registrar {
	public:
		Registrar() = delete;

		~Registrar() = default;

		explicit Registrar(ptr<T> object) : object(object) {}

		[[nodiscard]]
		std::weak_ptr<T> getAsBase() const { return std::weak_ptr<T>(object); }

		template <DerivedFrom<T> D>
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
		ptr<T> object;
	};

}
#endif