#include "pch.h"
#include"Data.hpp"

namespace SFS {

	template<typename T>
	void idVector<T>::push_back(const T& object)
	{
		this->objects.push_back(object);
	}
	
	template<typename T>
	void idVector<T>::push_back(const std::string& id, const T& object) {
		if (this->ids.contains(id))
			throw std::invalid_argument("ID: " + id + " already exist");
		this->objects.push_back(object);
		this->ids[id] = &this->objects.back();
	}

	template<typename T>
	void idVector<T>::push_back(T&& object)
	{
		this->objects.emplace_back(std::move(object));
	}

	template<typename T>
	void idVector<T>::push_back(const std::string& id, T&& object) {
		if (this->ids.contains(id))
			throw std::invalid_argument("ID: " + id + " already exist");
		this->objects.emplace_back(std::move(object));
		this->ids[id] = &this->objects.back();
	}

	template<typename T>
	void idVector<T>::erase(std::string id) {
		if (this->ids.contains(id)) {
			std::erase_if(this->objects, [](const T& object) { return &object == ids[id]; });
			this->ids.erase(id);
		}
		else {
			throw std::out_of_range("id: " + id + "  not found");
		}
	}

	template<typename T>
	void idVector<T>::erase(size_t index) {
		if (this->objects.size() > index) {
			std::erase_if(this->ids, [&](const auto& pair) { return pair.second == &objects[index]; });
			this->objects.erase(this->objects.begin() + index);
		}
		else
			throw std::out_of_range("index out of range");
	}

	template <typename T>
	T& idVector<T>::get(const size_t& index) const {
		if (this->objects.size() > index) {
			return this->objects[index];
		}
		else
			throw std::out_of_range("index out of range");
	}

	template <typename T>
	T& idVector<T>::get(const std::string& id) const {
		if (this->ids.contains(id)) {
			return *this->ids.at(id);
		}
		else
			throw std::out_of_range("id: " + id + " not found");
	}

	template <typename T>
	T& idVector<T>::operator[] (const size_t& index) const {
		return this.get(index);
	}

	template <typename T>
	T& idVector<T>::operator[] (const std::string& id) const {
		return this.get(id);
	}

}
