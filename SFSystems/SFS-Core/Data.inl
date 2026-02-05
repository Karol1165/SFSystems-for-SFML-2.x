#include "pch.h"
#include"Data.hpp"

namespace SFS {

	template<typename T>
	void idVector<T>::push_back(const T& object)
	{
		this->objects.push_back(object);
	}
	
	template<typename T>
	void idVector<T>::push_back(const T& object, const std::string& id) {
		if (this->ids.contains(id))
			throw std::invalid_argument("ID: " + id + " already exist");
		this->ids[id] = this->objects.size();
		this->objects.push_back(object);
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
		this->ids[id] = this->objects.size();
		this->objects.emplace_back(std::move(object));

	}

	template<typename T>
	void idVector<T>::erase(const std::string& id) {
		if (this->ids.contains(id)) {
			this->ids.erase(id);
			this->objects.erase(this->objects.begin() + this->ids.at(id));
			for (auto& pair : this->ids) {
				if (pair.second > this->ids.at(id)) {
					pair.second--;
				}
			}
		}
		else {
			throw std::out_of_range("id: " + id + "  not found");
		}
	}

	template<typename T>
	void idVector<T>::erase(size_t index) {
		if (this->objects.size() > index) {
			this->ids.erase(this->ids.find(index));
			this->objects.erase(this->objects.begin() + index);
			for (auto& pair : this->ids) {
				if (pair.second > index) {
					pair.second--;
				}
			}
		}
		else
			throw std::out_of_range("index out of range");
	}

	template <typename T>
	const T& idVector<T>::get(const size_t& index) const {
		if (this->objects.size() > index) {
			return this->objects[index];
		}
		else
			throw std::out_of_range("index out of range");
	}

	template <typename T>
	T& idVector<T>::get(const size_t& index) {
		if (this->objects.size() > index) {
			return this->objects[index];
		}
		else
			throw std::out_of_range("index out of range");
	}

	template <typename T>
	const T& idVector<T>::get(const std::string& id) const {
		if (this->ids.contains(id)) {
			return this->objects[this->ids.at(id)];
		}
		else
			throw std::out_of_range("id: " + id + " not found");
	}

	template <typename T>
	T& idVector<T>::get(const std::string& id) {
		if (this->ids.contains(id)) {
			return this->objects[this->ids.at(id)];
		}
		else
			throw std::out_of_range("id: " + id + " not found");
	}

	template <typename T>
	const T& idVector<T>::operator[] (const size_t& index) const {
		return this->get(index);
	}

	template <typename T>
	T& idVector<T>::operator[] (const size_t& index){
		return this->get(index);
	}

	template <typename T>
	const T& idVector<T>::operator[] (const std::string& id) const {
		return this->get(id);
	}

	template <typename T>
	T& idVector<T>::operator[] (const std::string& id) {
		return this->get(id);
	}

}
