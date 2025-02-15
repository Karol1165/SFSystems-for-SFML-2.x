#pragma once
#ifndef DATA_HPP_
#define DATA_HPP_
#include<SFML/Graphics.hpp>
#include<unordered_map>
#include "framework.h"
#include <memory>


namespace SFS {

	template <typename T>
	using ptr = std::unique_ptr<T>;


	template <typename V, typename T>
	concept isVariantOf = std::is_base_of_v<T, V>;

	template <typename T>
	inline ptr<T> make_ptr(T object) {
		return std::make_unique(object);
	}

	template <typename T, isVariantOf<T> O>
	inline O* GetFromPtr(ptr<T>& pointer) {
		return dynamic_cast<O*> (pointer.get());
	}


	struct SFS_C_API textData {
		int characterSize;
		sf::Color fillColor;
		sf::Color outlineColor;
		int outlineThickness;
	};
	SFS_C_API inline void setTextData(const textData& data, sf::Text& object) {
		object.setCharacterSize(data.characterSize);
		object.setFillColor(data.fillColor);
		object.setOutlineColor(data.outlineColor);
		object.setOutlineThickness(data.outlineThickness);
	}
	struct SFS_C_API rectangleShapeData {
		sf::Color fillColor;
		sf::Color outlineColor;
		sf::Vector2f size;
		int outlineThickness;
		sf::Texture texture;
	};
	SFS_C_API inline void setRectangleData(const rectangleShapeData& data, sf::RectangleShape& object) {
		object.setSize(data.size);
		object.setFillColor(data.fillColor);
		object.setOutlineColor(data.outlineColor);
		object.setOutlineThickness(data.outlineThickness);
		object.setTexture(&data.texture);
	}
	struct SFS_C_API circleShapeData {
		sf::Color fillColor;
		sf::Color outlineColor;
		int radius;
		int outlineThickness;
		sf::Texture texture;
	};
	SFS_C_API inline void setCircleData(const circleShapeData& data, sf::CircleShape& object) {
		object.setRadius(data.radius);
		object.setFillColor(data.fillColor);
		object.setOutlineColor(data.outlineColor);
		object.setOutlineThickness(data.outlineThickness);
		object.setTexture(&data.texture);
	}

	template <typename T>
	class idContainer {
	private:
		std::vector<T> objects;
		std::unordered_map<std::string, size_t> ids;
	public:

		void push_back(T object);
		void push_back(std::string id, T object);
		void erase(std::string id);
		void erase(size_t index);

		[[nodiscard]]
		T get(std::string id) const;

		[[nodiscard]]
		T get(size_t index) const;

		[[nodiscard]]
		T operator[] (std::string id) const;

		[[nodiscard]]
		T operator[] (size_t index) const;
	};
}

#endif 
