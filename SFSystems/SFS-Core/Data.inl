#include "pch.h"
#include"Data.hpp"

namespace SFS {

	template<typename T>
	void idContainer<T>::push_back(T object)
	{
		objects.push_back(object);
	}
	
	template<typename T>
	void idContainer<T>::push_back(std::string id, T object) {
		ids[id] = objects.size();
		objects.push_back(object);
	}

	template<typename T>
	void idContainer<T>::erase(std::string id) {
		if (ids.contains(id)) {
			objects.erase(objects.at(ids[id]));
			ids.erase(id);
		}
		else {
			throw std::out_of_range("id: " + id + "  not found");
		}
	}

	template<typename T>
	void idContainer<T>::erase(size_t index) {
		if (objects.size() > index) {
			objects.erase(objects.at(index));
			for (auto& i : ids)
			{
				if (ids[i] == index) {
					ids.erase(i);
					break;
				}
			}
		}
		else
		{
			throw std::out_of_range("index out of range");
		}
	}

	template <typename T>
	T idContainer<T>::get(std::string id) const {
		if(ids)
	}

}
